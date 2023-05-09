// Fill out your copyright notice in the Description page of Project Settings.


#include "XProjectileBase.h"
#include <Components\SphereComponent.h>
#include <GameFramework\ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <Misc\AssertionMacros.h>
#include <Kismet\GameplayStatics.h>
#include <Particles\ParticleSystem.h>
#include <Camera/CameraShakeBase.h>

// Sets default values
AXProjectileBase::AXProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 3.0f;
	CollisionComp = CreateDefaultSubobject<USphereComponent>("CollisionComp");
	RootComponent = CollisionComp;
	CollisionComp->OnComponentHit.AddDynamic(this, &AXProjectileBase::OnHit);
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(CollisionComp);

	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	ProjectileMoveComp->InitialSpeed = 8000.0f;
	ProjectileMoveComp->bRotationFollowsVelocity = true;
	ProjectileMoveComp->bInitialVelocityInLocalSpace = true;
	ProjectileMoveComp->ProjectileGravityScale = 0.0f;
	ImpactShakeInnerRadius = 0.0f;
	ImpactShakeOuterRadius = 1500.0f;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AXProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

// Called every frame
void AXProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXProjectileBase::Explode() {
	 if (ensure(IsValidChecked(this))) {
		UGameplayStatics::SpawnEmitterAtLocation(this, EmitterTemplate, GetActorLocation(), GetActorRotation());
	 	UGameplayStatics::PlayWorldCameraShake(this,ImpactShake,GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);
		Destroy();
	 }
}


