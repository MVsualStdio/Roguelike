// Fill out your copyright notice in the Description page of Project Settings.


#include "XPowerUpActor_Credits.h"
#include "XAttrributeComponent.h"
#include "XBlueprintFunctionLibrary.h"
#include "XPlayerState.h"
#include "Kismet/GameplayStatics.h"


void AXPowerUpActor_Credits::interactGet_Implementation(APawn* Pawn)
{
	AXPlayerState* State = Pawn->GetPlayerState<AXPlayerState>();
	//AXPlayerState* State = Cast<AXPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0));
	if(State && isVisable)
	{
		State->AddCredites(80);
		UXBlueprintFunctionLibrary::Debug("cE");
		Hiden();
	}
	
}
