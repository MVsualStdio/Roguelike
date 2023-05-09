// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "XAction.generated.h"

class UXActionComponent;
class UXActionActorComponent;
/**
 * 
 */
USTRUCT()
struct FRepDataStruct
{
	GENERATED_BODY();
	UPROPERTY()
	bool IsRunning;
	UPROPERTY()
	AActor* Instagtor;
};


UCLASS(Blueprintable)
class LEARN_API UXAction : public UObject
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	UXActionActorComponent* GetOuterComponent() const;
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTag;
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockTag;
	UPROPERTY(ReplicatedUsing="OnRep_Data")
	FRepDataStruct RepData;
	UPROPERTY(Replicated)
	UXActionActorComponent* ActionComp;
	UFUNCTION()
	void OnRep_Data();
public:
	UPROPERTY(Replicated)
	float TimeStart;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	UTexture2D* Icone;
	UPROPERTY(EditDefaultsOnly,Category="Action")
	FName ActionName;
	UPROPERTY(EditDefaultsOnly,Category="Action")
	bool AutoStart;
	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* Actor);
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action")
	void StopAction(AActor* Actor);
	UFUNCTION(BlueprintNativeEvent,Category="Action")
	bool CanStart(AActor* Actor);
	UFUNCTION()
	virtual UWorld* GetWorld() const override;
	UFUNCTION(BlueprintCallable,Category="Action")
	bool GetRunning(); 
	UFUNCTION()
	void InitActionComp(UXActionActorComponent* Action);
	bool IsSupportedForNetworking() const override
	{
		return true;
	}
};

