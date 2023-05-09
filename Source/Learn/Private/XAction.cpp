// Fill out your copyright notice in the Description page of Project Settings.


#include "XAction.h"
#include "Net/UnrealNetwork.h"
#include"XActionActorComponent.h"

void UXAction::InitActionComp(UXActionActorComponent* Action)
{
	ActionComp = Action;
}


void UXAction::StartAction_Implementation(AActor* Actor)
{
	UXActionActorComponent* Component =  GetOuterComponent();
	Component->ActivateGameTag.AppendTags(GrantsTag);
	RepData.IsRunning = true;
	RepData.Instagtor = Actor;
	GetOuterComponent()->OnActionStart.Broadcast(GetOuterComponent(),this);
	if(GetOuterComponent()->GetOwnerRole() == ROLE_Authority)
	{
		TimeStart = GetWorld()->TimeSeconds;
	}
	
}


void UXAction::StopAction_Implementation(AActor* Actor)
{
	UXActionActorComponent* Component =  GetOuterComponent();
	Component->ActivateGameTag.RemoveTags(GrantsTag);
	// ensureAlways(IsRunning);
	RepData.IsRunning = false;
	RepData.Instagtor = Actor;
	GetOuterComponent()->OnActionStop.Broadcast(GetOuterComponent(),this);
}

bool UXAction::CanStart_Implementation(AActor* Actor)
{
	if(RepData.IsRunning)
	{
		return false;
	}
	UXActionActorComponent* Component =  GetOuterComponent();
	if(Component->ActivateGameTag.HasAny(BlockTag))
	{
		return false;
	}
	return true;
}


UWorld* UXAction::GetWorld() const
{
	AActor* ActorComponent  = Cast<AActor>(GetOuter());

	if(ActorComponent)
	{
		return ActorComponent->GetWorld();
	}
	return nullptr;
}

UXActionActorComponent* UXAction::GetOuterComponent() const
{
	return ActionComp;
}

bool UXAction::GetRunning()
{
	return  RepData.IsRunning;
}

void UXAction::OnRep_Data()
{
	if(RepData.IsRunning)
	{
		StartAction(RepData.Instagtor);
	}
	else
	{
		StopAction(RepData.Instagtor);
	}
}

void UXAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXAction, RepData);
	DOREPLIFETIME(UXAction, ActionComp);
	DOREPLIFETIME(UXAction,TimeStart);
}

