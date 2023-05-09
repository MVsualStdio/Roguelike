// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XPowerUpActor.h"
#include "XPowerUpActor_Healthy.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API AXPowerUpActor_Healthy : public AXPowerUpActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	int CreaitsCost;
public:
	AXPowerUpActor_Healthy();
	virtual void interactGet_Implementation(APawn* Pawn) override;
	virtual FText GetInteractText_Implementation(APawn* Pawn) override;
};
