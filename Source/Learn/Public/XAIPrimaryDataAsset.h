// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XAction.h"
#include "AI/XAICharacter.h"
#include "Engine/DataAsset.h"
#include "XAIPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API UXAIPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category="Info")
	TSubclassOf<AXAICharacter> Character;
	UPROPERTY(EditAnywhere,Category="Info")
	TArray<TSubclassOf<UXAction>> Action;
	UPROPERTY(EditAnywhere,Category="Info")
	UTexture2D* Icon;
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("AI",GetFName());
	}
};
