// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XGameInterface.h"
#include "GameFramework/Actor.h"
#include "XPowerUpActor.generated.h"

UCLASS()
class LEARN_API AXPowerUpActor : public AActor ,public IXGameInterface 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXPowerUpActor();
	UPROPERTY(ReplicatedUsing="OnRep_Hiden",BlueprintReadOnly)
	bool isVisable;
	UFUNCTION()
	void OnRep_Hiden();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="Mesh")
	UStaticMeshComponent* MeshComp;

	// UFUNCTION(NetMulticast)
	// void ServerHiden();
	void Exist();
	void Hiden();
	UPROPERTY(EditAnywhere,Category="Time")
	float CoverTime;
	FTimerHandle TimeHandle;
	UPROPERTY(EditAnywhere,Category="Healthy")
	float CreateHealthy;
public:
	virtual void interactGet_Implementation(APawn* Pawn) override;
	virtual FText GetInteractText_Implementation(APawn* Pawn) override;
	//static bool IsHinden(AActor* Actor);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
