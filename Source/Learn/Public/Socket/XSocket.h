// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XSocket.generated.h"

UCLASS()
class LEARN_API AXSocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXSocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FSocket* Socket;
	bool connected;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void SendMsg();
};
