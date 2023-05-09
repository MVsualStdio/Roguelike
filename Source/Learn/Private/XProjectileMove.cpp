// Fill out your copyright notice in the Description page of Project Settings.


#include "XProjectileMove.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

AXProjectileMove::AXProjectileMove()
{
	//this->CollisionComp->OnComponentBeginOverlap.AddDynamic(this,&AXProjectileMove::OnActorOverlap);
	
}

void AXProjectileMove::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandle,this,&AXProjectileMove::Explode,0.2f);
}


void AXProjectileMove::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, EmitterTemplate, GetActorLocation(), GetActorRotation());
	EffectComp->DeactivateSystem();
	ProjectileMoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);
	FTimerHandle TimerHandleMoveLocation;
	GetWorldTimerManager().SetTimer(TimerHandleMoveLocation,this,&AXProjectileMove::TimerMoveToLoction,0.2f);
	//Super::Explode();
}

void AXProjectileMove::TimerMoveToLoction()
{
	FVector ActorLoc =  GetActorLocation();
	AActor* ower =  GetInstigator();
	ower->TeleportTo(ActorLoc,ower->GetActorRotation(),false,false);
	Destroy();
}

void AXProjectileMove::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ensure(OtherActor) && GetInstigator() != OtherActor) {
			Explode();
	}
}

