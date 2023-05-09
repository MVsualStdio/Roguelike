// Fill out your copyright notice in the Description page of Project Settings.


#include "XActionActorComponent.h"
#include "XAction.h"
#include "XBlueprintFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

// Sets default values for this component's properties
UXActionActorComponent::UXActionActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UXActionActorComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->HasAuthority())
	{
		for(TSubclassOf<UXAction> ActionClass : DefaultActions)
		{
			AddAction(GetOwner(),ActionClass);
		}
	}
	
	// ...
	
}


// Called every frame
void UXActionActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UXActionActorComponent::AddAction(AActor* Instagtor,TSubclassOf<UXAction> Action)
{
	if(!Action)
	{
		return;
	}
	UXAction* newAction = NewObject<UXAction>(GetOwner(),Action);
	if(newAction)
	{
		
		newAction->InitActionComp(this);
		Actions.Add(newAction);
		if(newAction->AutoStart && newAction->CanStart(Instagtor))
		{
			newAction->StartAction(Instagtor);
		}
	}
	
}

void UXActionActorComponent::RemoveAction(UXAction* Action)
{
	if(Action && !Action->GetRunning())
	{
		Actions.Remove(Action);
	}
	
}


bool UXActionActorComponent::StartActionByName(AActor* Instigator, FName ActorName)
{
	
	for (UXAction* Action : Actions)
	{
		//!Action->IsUnreachable()
		if(!Action->IsUnreachable() && Action->ActionName == ActorName)
		{
			if(!Action->CanStart(Instigator))
			{
				continue;
			}
			if(!GetOwner()->HasAuthority())
			{
				ServerStartAction(Instigator,ActorName);
			}
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UXActionActorComponent::StopActionByName(AActor* Instigator, FName ActorName)
{
	for (UXAction* Action : Actions)
	{
		if(Action && Action->ActionName == ActorName)
		{
			if(!GetOwner()->HasAuthority())
			{
				ServerStopAction(Instigator,ActorName);
			}
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;
}

void UXActionActorComponent::ServerStartAction_Implementation(AActor* Instigator, FName ActorName)
{
	StartActionByName(Instigator,ActorName);
}

void UXActionActorComponent::ServerStopAction_Implementation(AActor* Instigator, FName ActorName)
{
	StopActionByName(Instigator,ActorName);
}


void UXActionActorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXActionActorComponent, Actions);
}

bool UXActionActorComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for (UXAction* Action : Actions)
	{
		if (Action)
		{
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}

 	return WroteSomething;
}