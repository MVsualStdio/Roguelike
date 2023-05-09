// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XProjectileBase.h"
#include "XProjectileBlack.generated.h"

class URadialForceComponent;
/**
 * 
 */
UCLASS()
class LEARN_API AXProjectileBlack : public AXProjectileBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;
public:
	AXProjectileBlack();
	void BeginPlay() override;
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
