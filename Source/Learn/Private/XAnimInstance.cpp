 // Fill out your copyright notice in the Description page of Project Settings.


#include "XAnimInstance.h"

#include "GameplayTagContainer.h"
#include "XAction.h"
#include "XActionActorComponent.h"

 void UXAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
 	AActor* Actor = GetOwningActor();
 	if(Actor)
 	{
 		ActionComponent = Cast<UXActionActorComponent>(Actor->GetComponentByClass(UXActionActorComponent::StaticClass()));
 	}
}

void UXAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    static FGameplayTag StunnedTag = FGameplayTag::RequestGameplayTag("Status.Stunned");
 	if(ActionComponent)
 	{
 		IsStunned = ActionComponent->ActivateGameTag.HasTag(StunnedTag);
 	}
}

