// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "XPlayerState.generated.h"

class UXSaveGame;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FonCreditesChange, AXPlayerState*, PlayState, int32, NewCredits, int32,
                                               Delta);
/**
 * 
 */



UCLASS()
class LEARN_API AXPlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	UPROPERTY(ReplicatedUsing="Rep_CreditsChange",Replicated)
	//UPROPERTY(Replicated)
	int Credits;
	UFUNCTION()
	void Rep_CreditsChange(int OldCredits);
	// UFUNCTION(NetMulticast,Reliable)
	// void NetMulticastCreditsChange(int Cre,int32 Delta);

public:
	AXPlayerState();
	UFUNCTION(BlueprintCallable,Category="Credits")
	void AddCredites(int32 Delta);
	
	UFUNCTION(BlueprintCallable,Category="Credits")
	bool RemoveCredites(int32 Delta);
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FonCreditesChange OnCreditsChanged;
	UFUNCTION(Server,Reliable,Category="Credits")
	void ServerAddCredites(int32 Delta);

	UFUNCTION(BlueprintCallable)
	int GetCredits();
	
	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(UXSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(UXSaveGame* SaveObject);
};
