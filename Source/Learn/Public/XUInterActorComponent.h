// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XGameInterface.h"
#include "XUInterActorComponent.generated.h"


class UXWorldMyUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN_API UXUInterActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXUInterActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	AActor* ForceActor;
	UPROPERTY(EditAnywhere,Category="UI")
	TSubclassOf<UXWorldMyUserWidget> UserWidgetClass;
	UPROPERTY()
	UXWorldMyUserWidget* UI;
	
	UFUNCTION(Server,Reliable)
	void ServerInteract(AActor* Infocus);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void FindInteract();
	void PrimaryInterAct();
		
};
