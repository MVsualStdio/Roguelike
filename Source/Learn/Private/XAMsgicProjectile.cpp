// Fill out your copyright notice in the Description page of Project Settings.


#include "XAMsgicProjectile.h"
#include <Components\SphereComponent.h>
#include <GameFramework\ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include "XAttrributeComponent.h"
#include <Components\AudioComponent.h>
#include  <Sound/SoundCue.h>

#include "XAction.h"
#include "XActionActorComponent.h"
#include "XAction_Effect.h"
#include "XBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AXAMsgicProjectile::AXAMsgicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Super::AXProjectileBase();
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AXAMsgicProjectile::OnActorOverlap);
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
}

// Called when the game starts or when spawned
void AXAMsgicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXAMsgicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation(),GetActorRotation());
	}
	
}


void AXAMsgicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//&& Cast<AActor>(OtherActor->GetInstigator()) != OtherActor
	if (OtherActor && GetInstigator() != OtherActor) {
		UXActionActorComponent* ActionComp = Cast<UXActionActorComponent>(OtherActor->GetComponentByClass(UXActionActorComponent::StaticClass()));
		if (ActionComp && ActionComp->ActivateGameTag.HasTag(ParryTag))
		{
			ProjectileMoveComp->Velocity = -ProjectileMoveComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}
		
		if(UXBlueprintFunctionLibrary::ApplyActorDamage(OtherActor,GetInstigator(),-20.f,SweepResult))
		{
			Super::Explode();
			// if (GEngine) {
			// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("456"));
			// }
			if(ActionComp && HasAuthority())
			{
				ActionComp->AddAction(GetInstigator(),Effect);
				// if (GEngine) {
				// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("123"));
				// }
			}
		}

		
		// UXAttrributeComponent* attribute = Cast<UXAttrributeComponent>(OtherActor->GetComponentByClass(UXAttrributeComponent::StaticClass()));
		// if (attribute) {
		// 	// if (GEngine) {
		// 	//  	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Heatlthy:11")));
		// 	// }
		// 	attribute->AlterHealthy(GetInstigator(),-20.0f);
		// 	Super::Explode();
		// }
	}
}
