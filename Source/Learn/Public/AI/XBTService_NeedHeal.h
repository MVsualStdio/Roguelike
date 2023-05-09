// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "XBTService_NeedHeal.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API UXBTService_NeedHeal : public UBTService
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector NeedHealKey;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
