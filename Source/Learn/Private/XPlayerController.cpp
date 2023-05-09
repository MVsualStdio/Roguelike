// Fill out your copyright notice in the Description page of Project Settings.


#include "XPlayerController.h"

#include "Blueprint/UserWidget.h"


void AXPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	OnPawnChange.Broadcast(InPawn);
}


void AXPlayerController::BeginPlayingState()
{
	BlueprintBeginPlayingState();
}
//
void AXPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	OnPlayerStateReceived.Broadcast(PlayerState);
}

void AXPlayerController::ToPauseMenu()
{

	if(ParserWidget)
	{
		ParserWidget->RemoveFromParent();
		ParserWidget = nullptr;
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		return ;
	}
	ParserWidget = CreateWidget<UUserWidget>(this,ParserWidegtClass);
	if(ParserWidget)
	{
		ParserWidget->AddToViewport(100);
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

void AXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("PauseMenu",IE_Pressed,this,&AXPlayerController::ToPauseMenu);
}

