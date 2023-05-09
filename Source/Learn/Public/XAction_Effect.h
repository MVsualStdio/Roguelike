// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XAction.h"
#include "XAction_Effect.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API UXAction_Effect : public UXAction
{
	GENERATED_BODY()
protected:
	FTimerHandle DuationHandle;
	FTimerHandle PeriodHandle;
	UPROPERTY(EditAnywhere,Category="Effect")
	int Effect;
	UPROPERTY(EditAnywhere,Category="Effect")
	float Duation;
	UPROPERTY(EditAnywhere,Category="Effect")
	float Period;
public:
	UFUNCTION()
	void StartAction_Implementation(AActor* Actor) override;
	UFUNCTION()
	void StopAction_Implementation(AActor* Actor) override;
	UFUNCTION(BlueprintNativeEvent,Category="Effect")
	void ExecEffect(AActor* Instigator);
	UXAction_Effect();
	UFUNCTION(BlueprintCallable)
	float GetTimeRemain();
	UFUNCTION(BlueprintCallable)
	float GetPeriod();
};
