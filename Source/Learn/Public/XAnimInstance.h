// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "XAnimInstance.generated.h"

class UXActionActorComponent;
/**
 * 
 */
UCLASS()
class LEARN_API UXAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Animation")
	bool IsStunned;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Animation")
	UXActionActorComponent* ActionComponent;
	void NativeInitializeAnimation() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;
};
