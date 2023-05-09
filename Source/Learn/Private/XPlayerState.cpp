// Fill out your copyright notice in the Description page of Project Settings.


#include "XPlayerState.h"

#include "XSaveGame.h"
#include "Net/UnrealNetwork.h"

AXPlayerState::AXPlayerState()
{
	// bReplicates = true;
}


void AXPlayerState::AddCredites(int32 Delta)
{
	// Avoid user-error of adding a negative amount or zero
	if (!ensure(Delta > 0.0f))
	{
		return;
	}
	Credits += Delta;
	//NetMulticastCreditsChange(Credits,Delta);
	OnCreditsChanged.Broadcast(this, Credits, Delta);
	
}


bool AXPlayerState::RemoveCredites(int32 Delta)
{
	// Avoid user-error of adding a subtracting negative amount or zero
	if (!ensure(Delta > 0.0f))
	{
		return false;
	}

	if (Credits < Delta)
	{
		// Not enough credits available
		return false;
	}

	Credits -= Delta;
	//NetMulticastCreditsChange(Credits,Delta);
	OnCreditsChanged.Broadcast(this, Credits, -Delta);

	return true;
}

void AXPlayerState::ServerAddCredites_Implementation(int32 Delta)
{
	AddCredites(Delta);
}

int AXPlayerState::GetCredits()
{
	return Credits;
}

void AXPlayerState::LoadPlayerState_Implementation(UXSaveGame* SaveObject)
{
	Credits =  SaveObject->Credits;
}

void AXPlayerState::SavePlayerState_Implementation(UXSaveGame* SaveObject)
{
	SaveObject->Credits = Credits;
}

void AXPlayerState::Rep_CreditsChange(int OldCredits)
{
 	//UE_LOG(LogTemp,Log,TEXT("Cres:%d,Old:%d"),Credits,OldCredits);
 	//NetMulticastCreditsChange(Credits - OldCredits);
 	OnCreditsChanged.Broadcast(this, Credits, Credits-OldCredits);
}

void AXPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXPlayerState,Credits);
}
// void AXPlayerState::NetMulticastCreditsChange_Implementation(int Cre,int32 Delta)
// {
// 	OnCreditsChanged.Broadcast(this, Cre, Delta);
// }

