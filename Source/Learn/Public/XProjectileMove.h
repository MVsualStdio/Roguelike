// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XProjectileBase.h"
#include "XProjectileMove.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API AXProjectileMove : public AXProjectileBase
{
	GENERATED_BODY()

public:
	AXProjectileMove();
public:
	void Explode() override;
	FTimerHandle TimeHandle;
	void TimerMoveToLoction();
	void BeginPlay() override;
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
