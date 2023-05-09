// Fill out your copyright notice in the Description page of Project Settings.


#include "XProjectileBlack.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"

AXProjectileBlack::AXProjectileBlack()
{
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	RadialForceComp->Radius = 1000.0f;
	RadialForceComp->ForceStrength = -2000000.0f;
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this,&AXProjectileBlack::OnActorOverlap);
	RadialForceComp->SetAutoActivate(true);
	RadialForceComp->bImpulseVelChange = true;
	//RadialForceComp->AddObjectTypeToAffect(TEnumAsByte<ObjectTypeQuery1>(APawn));
}

void AXProjectileBlack::BeginPlay()
{
	Super::BeginPlay();
	//RadialForceComp->FireImpulse();
	//FTimerHandle TimeHandle;
	//GetWorldTimerManager().SetTimer(TimeHandle,this,&AXProjectileBase::Explode,2.0f);
}

void AXProjectileBlack::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (ensure(OtherActor) && GetInstigator() != OtherActor) {
		if(OtherComp->IsSimulatingPhysics())
		{
			OtherActor->Destroy();
		}
		//Explode();
	//}
}
