// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API UXBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="GamePlay")
	static bool ApplyDamage(AActor* DamageActor,AActor* TargetActor,float Damage);
	UFUNCTION(BlueprintCallable,Category="GamePlay")
	static bool ApplyActorDamage(AActor* DamageActor,AActor* TargetActor,float Damage,const FHitResult& HitResult);
	UFUNCTION()
	static void Debug(FString Str);
};
