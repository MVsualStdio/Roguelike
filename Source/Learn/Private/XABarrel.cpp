// Fill out your copyright notice in the Description page of Project Settings.


#include "XABarrel.h"
#include <Components\SphereComponent.h>
#include <Components\StaticMeshComponent.h>
#include <Particles\ParticleSystemComponent.h>
#include <PhysicsEngine\RadialForceComponent.h>

#include "XAttrributeComponent.h"
// Sets default values
AXABarrel::AXABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);
	//MeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	MeshComp->SetSimulatePhysics(true);

	//MeshComp->SetNotifyRigidBodyCollision(true);
	//MeshComp->SetCollisionProfileName("BlockAll");
	//MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(MeshComp);
	EffectComp->SetVisibility(false);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadiaForceComp");
	RadialForceComp->SetupAttachment(MeshComp);
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->ImpulseStrength = 2500.0f;
	RadialForceComp->Radius = 1000.0f;
	//RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	
}

// Called when the game starts or when spawned
void AXABarrel::BeginPlay()
{
	Super::BeginPlay();
	
}


void AXABarrel::PostInitializeComponents() {
	Super::PostInitializeComponents();
	MeshComp->OnComponentHit.AddDynamic(this, &AXABarrel::OnHit);
}

// Called every frame
//void AXABarrel::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

//void AXABarrel::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("overlap Begin!"));
//}

void AXABarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CubeHit1"));
	//}
	
	ECollisionChannel HitType = OtherComp->GetCollisionObjectType();
	if (HitType == ECC_WorldDynamic || HitType == ECC_Pawn) {
		
		UXAttrributeComponent* attribute =  Cast<UXAttrributeComponent>(OtherActor->GetComponentByClass(UXAttrributeComponent::StaticClass())) ;
		if(attribute)
		{
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hero"));
			}
			attribute->AlterHealthy(OtherActor,-20.0f);
			
		}
		EffectComp->SetVisibility(true);
		EffectComp->Activate(true);
		RadialForceComp->FireImpulse();
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CubeHit"));
		}
		//MeshComp->DestroyComponent(true);
		//Destroy();
	}

}

