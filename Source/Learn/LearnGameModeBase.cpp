// Copyright Epic Games, Inc. All Rights Reserved.


#include "LearnGameModeBase.h"

void ALearnGameModeBase::StartPlay() {
	Super::StartPlay();
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameModeBase!"));
}