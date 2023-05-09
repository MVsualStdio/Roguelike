// Fill out your copyright notice in the Description page of Project Settings.


#include "XAction_Effect.h"
#include "XActionActorComponent.h"
#include "XBlueprintFunctionLibrary.h"
#include "XPlayerState.h"
#include "GameFramework/GameStateBase.h"


UXAction_Effect::UXAction_Effect()
{
	AutoStart = true;
}


void UXAction_Effect::StartAction_Implementation(AActor* Actor)
{
	Super::StartAction_Implementation(Actor);
	if(Duation > 0)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"ExecEffect",  Actor);
		GetWorld()->GetTimerManager().SetTimer(DuationHandle,Delegate,Duation,true);
	}
	if(Period > 0)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"StopAction",  Actor);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle,Delegate,Period,false);
	}
}

void UXAction_Effect::StopAction_Implementation(AActor* Actor)
{
	// if(GetWorld()->GetTimerManager().GetTimerRemaining(DuationHandle) < KINDA_SMALL_NUMBER)
	// {
	// 	ExecEffect(Actor);
	// }
	Super::StopAction_Implementation(Actor);
	
	GetWorld()->GetTimerManager().ClearTimer(DuationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);

	UXActionActorComponent* Component =  GetOuterComponent();
	if(Component)
	{
		Component->RemoveAction(this);
	}
}


void UXAction_Effect::ExecEffect_Implementation(AActor* Instigator)
{
	FHitResult HitResult;
	UXBlueprintFunctionLibrary::ApplyActorDamage(GetOuterComponent()->GetOwner(),Instigator,-4,HitResult);
	// if (GEngine) {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CubeHit1"));
	// }
}

float UXAction_Effect::GetTimeRemain()
{
	AGameStateBase* GS = GetWorld()->GetGameState<AGameStateBase>();
	if(GS)
	{
			float EndTime = TimeStart + Period;
        	
        	return EndTime - GS->GetServerWorldTimeSeconds();
	}
	return 0.0f;
}

float UXAction_Effect::GetPeriod()
{
	return  Period;
}
