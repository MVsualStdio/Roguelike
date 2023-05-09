// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "XProjectileBase.h"
#include "XAMsgicProjectile.generated.h"

class UXAction_Effect;
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class AXProjectileBase;
class USoundCue;

UCLASS()
class LEARN_API AXAMsgicProjectile : public AXProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXAMsgicProjectile();
protected:
	UPROPERTY(EditAnywhere,Category="Tag")
	FGameplayTag ParryTag;
	UPROPERTY(EditAnywhere,Category="Tag")
	TSubclassOf<UXAction_Effect> Effect;
	UPROPERTY(EditAnywhere)
	USoundCue* HitSound;
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
