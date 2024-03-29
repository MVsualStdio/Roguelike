// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEARN_API IXGameInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void interactGet(APawn* Pawn);
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	FText GetInteractText(APawn* Pawn);
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void IntergetOnLoad();
	
};
