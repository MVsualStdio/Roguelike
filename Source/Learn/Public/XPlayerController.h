// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChange,APawn*, Pawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, APlayerState*, NewPlayerState);
/**
 * 
 */
UCLASS()
class LEARN_API AXPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UUserWidget* ParserWidget;
	UPROPERTY(EditAnywhere,Category="UI")
	TSubclassOf<UUserWidget> ParserWidegtClass;
	UFUNCTION(BlueprintCallable)
	void ToPauseMenu();
	void SetupInputComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnPawnChange OnPawnChange;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateChanged OnPlayerStateReceived;
	
	virtual void BeginPlayingState() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintBeginPlayingState();

	void OnRep_PlayerState() override;
	
	UFUNCTION(BlueprintCallable)
	void SetPawn(APawn* InPawn) override;
};
