// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XAction.h"
#include "XAction_Projectile.generated.h"

/**
 * 
 */
class UXAction;
class UXActionComponent;
class UCameraComponent;
class UAnimMontage;

UCLASS()
class LEARN_API UXAction_Projectile : public UXAction
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;
	
	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere,Category = "Attack")
	TSubclassOf<AActor> Spawn;
public:
	UXAction_Projectile();
	UFUNCTION()
	void SpawnProjectile(ACharacter* Character);
	void StartAction_Implementation(AActor* Actor) override;
	void StopAction_Implementation(AActor* Actor) override;
	
	
};

