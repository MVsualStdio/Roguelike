// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XAttrributeComponent.h"
#include "GameFramework/Character.h"
#include "XAICharacter.generated.h"

class UXActionActorComponent;
class UXWorldMyUserWidget;
class UPawnSensingComponent;
UCLASS()
class LEARN_API AXAICharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,Category="UI")
	TSubclassOf<UXWorldMyUserWidget> WorldClass;
	// UPROPERTY(EditAnywhere,Category="UI")
	// UXWorldMyUserWidget* Widget;
public:
	// Sets default values for this character's properties
	AXAICharacter();
	UPROPERTY(EditAnywhere,Category="AI")
	FName AIName;
protected:
	
	UPROPERTY(EditDefaultsOnly,Category="UI")
	UXActionActorComponent* ActionComp;
	UPROPERTY(EditDefaultsOnly,Category="UI")
	UXWorldMyUserWidget* WorldWidget;
	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UUserWidget> HealthyWidget;
	UPROPERTY(EditAnywhere,Category="Effect")
	FName ParHitMa;
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
	UPROPERTY(EditAnywhere,Category="AI")
	UPawnSensingComponent* SensingComp;
	UFUNCTION()
	void OnSence(APawn* Pawn);
	UPROPERTY(EditAnywhere,Category="AI")
	UXAttrributeComponent* AttributeComp;
	void SetTargetActor(AActor* Actor);
	AActor* GetTargetActor();
	UFUNCTION()
	void OnHealthyChanges(AActor* Actor, UXAttrributeComponent* ownComp, float Healthy, float Delt);
};
