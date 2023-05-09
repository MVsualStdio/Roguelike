// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "XGameMode.generated.h"

class UXAIPrimaryDataAsset;
class UXSaveGame;
class AXPlayerChacter;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FAIRow : public  FTableRowBase
{
	GENERATED_BODY()

	FAIRow()
	{
		Weight = 1.0f;
		SpawnCost = 1.0f;
		KillReward = 20.0f;
	}
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AI")
	FPrimaryAssetId AIId;
	//UXAIPrimaryDataAsset* AICharector;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AI")
	float Weight;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AI")
	float SpawnCost;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AI")
	float KillReward;
};


UCLASS()
class LEARN_API AXGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,Category="Data")
	UDataTable* DataTable;
	UPROPERTY(EditAnywhere,Category="Player")
	float DelayTime;
	// UPROPERTY(EditAnywhere,Category="AI")
	// TSubclassOf<AActor> AICharector;
	// UPROPERTY(EditAnywhere,Category="AI")
	// int32 MaxAINums;
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UEnvQuery* QueryTemplate;
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UCurveFloat* Curve;
	FTimerHandle TimeHandle;
	virtual void SpawnAI();
	UFUNCTION()
	void SpawnAIQuery(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	UFUNCTION()
	void Respawn(AController* Controller);
public:
	AXGameMode();
	virtual void StartPlay() override;
	void ActorOnKilled(AActor* KilledActor,AActor* OtherActor);

	UFUNCTION(BlueprintCallable,Category="SaveGame")
	void SaveGame();
	UFUNCTION()
	void LoadGame();
	UFUNCTION()
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);
protected:
	FString SlotName;
	UXSaveGame* CurrentSaveGame;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
};

