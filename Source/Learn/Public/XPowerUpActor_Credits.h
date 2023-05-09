// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XPowerUpActor.h"
#include "XPowerUpActor_Credits.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API AXPowerUpActor_Credits : public AXPowerUpActor
{
	GENERATED_BODY()
public:
	virtual void interactGet_Implementation(APawn* Pawn) override;
};
