// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XAttrributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnChangeHealthy,AActor*,actor,UXAttrributeComponent*,ownComp,float,Healthy,float,delt);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN_API UXAttrributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXAttrributeComponent();
	UFUNCTION(BlueprintCallable,Category="Attribute")
	static bool IsActorLive(AActor* Actor);
protected:
	
	// Called when the game starts
	//virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,ReplicatedUsing="OnRep_CurrentHealth")
    float healthy;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated)
	float MaxHealthy;
	// UFUNCTION(NetMulticast,Reliable)
	// void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);
	UFUNCTION()
	void OnRep_CurrentHealth(float oldhealthy);
public:	
	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnChangeHealthy healthyChange;
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	bool IsAlive();
	UFUNCTION(BlueprintCallable)
	bool AlterHealthy(AActor* Instor,float delt);
	UFUNCTION(BlueprintCallable)
	float GetHealthy();
	UFUNCTION(BlueprintCallable)
	float GetMaxHealthy();
	UFUNCTION(BlueprintCallable)
	bool isFullHealthy();
	//UFUNCTION(Server,Reliable)
	//void ServerAlterHealthy(AActor* Instagtor,float delt);
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
