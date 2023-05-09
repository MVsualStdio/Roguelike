// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XGameInterface.h"
#include "XASitme.generated.h"

class UStaticMeshComponent;

UCLASS()
class LEARN_API AXASitme : public AActor ,public IXGameInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	float TargetRotation;
	virtual  void interactGet_Implementation(APawn* Pawn) override;
	// Sets default values for this actor's properties
	AXASitme();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(ReplicatedUsing="OnRep_LidOpened",BlueprintReadOnly,SaveGame)
	bool LidOpened;

	UFUNCTION()
	void OnRep_LidOpened();

	UFUNCTION()
	virtual void IntergetOnLoad_Implementation() override;
};
