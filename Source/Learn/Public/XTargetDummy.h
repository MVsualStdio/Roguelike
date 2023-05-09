// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XTargetDummy.generated.h"

class UXAttrributeComponent;
class UStaticMeshComponent;


UCLASS()
class LEARN_API AXTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXTargetDummy();
protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere)
	UXAttrributeComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* staticComp;
	UFUNCTION()
	void OnHealthyChanges(AActor* Actor,UXAttrributeComponent* ownComp,float Healthy,float Delt);

};
