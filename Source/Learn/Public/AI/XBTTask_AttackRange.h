// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XProjectileBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "XBTTask_AttackRange.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API UXBTTask_AttackRange : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
protected:
	UPROPERTY(EditAnywhere,Category="AI")
	TSubclassOf<AXProjectileBase> ProjectileClass;
};
