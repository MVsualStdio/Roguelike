// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "XActionActorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FonActionStateChange, UXActionActorComponent* ,OwningComp,UXAction*,Action);

struct FGameplayTagContainer;


class UXAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN_API UXActionActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UXActionActorComponent();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GameTag")
	FGameplayTagContainer ActivateGameTag;
protected:
	UPROPERTY(EditAnywhere,Category="Action")
	TArray<TSubclassOf<UXAction>> DefaultActions;
	UPROPERTY(BlueprintReadOnly,Replicated)
	TArray<UXAction*> Actions;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void AddAction(AActor* Instagtor,TSubclassOf<UXAction> Action);
	UFUNCTION(BlueprintCallable)
	void RemoveAction(UXAction* Action);
	UFUNCTION(BlueprintCallable)
	bool StartActionByName(AActor* Instigator,FName ActorName);
	UFUNCTION(BlueprintCallable)
	bool StopActionByName(AActor* Instigator,FName ActorName);
	UFUNCTION(Server,Reliable)
	void ServerStartAction(AActor* Instigator,FName ActorName);
	UFUNCTION(Server,Reliable)
	void ServerStopAction(AActor* Instigator,FName ActorName);
	// UFUNCTION(Server,Reliable)
	// void ServerStartAction(AActor* Instigator,FName ActorName);
	// UFUNCTION(NetMulticast,Reliable)
	// void ClientStartAction(AActor* Instigator,FName ActorName);
	
	bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	UPROPERTY(BlueprintAssignable)
	FonActionStateChange OnActionStart;
	UPROPERTY(BlueprintAssignable)
	FonActionStateChange OnActionStop;
};
