// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XPlayerChacter.generated.h"

class UXAction;
class UXActionComponent;
class UCameraComponent;
class USpringArmComponent;
class AXAMsgicProjectile;
class UXUInterActorComponent;
class UXAttrributeComponent;

class UXActionActorComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class LEARN_API AXPlayerChacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXPlayerChacter();

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	UXUInterActorComponent* ActorComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXAttrributeComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UXActionActorComponent* ActionComp;
	
protected:
	virtual void BeginPlay() override;
	void Jump();
	void Forward(float value);
	void MoveLeftorRight(float value);
	void Look(float value);
	void OpenBox();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FOnDeath OnDeath;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void OnHealthyChanges(AActor* Actor,UXAttrributeComponent* ownComp,float Healthy,float Delt);
	UFUNCTION()
	virtual void PostInitializeComponents() override;
	virtual FVector GetPawnViewLocation() const override;
public:
	void SprintRuning();
	void SprintStopRuning();
	void ProjectileAttack();
	void StartParry();
	void StopParry();
};
