// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "XAIController.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API AXAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* AIBT;
public:
	virtual void BeginPlay() override;
};
