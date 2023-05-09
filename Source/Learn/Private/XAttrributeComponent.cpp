// Fill out your copyright notice in the Description page of Project Settings.


#include "XAttrributeComponent.h"
#include "XGameMode.h"
#include "Learn/Learn.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UXAttrributeComponent::UXAttrributeComponent()
{
	healthy = 100;
	MaxHealthy = 100;
	SetIsReplicatedByDefault(true);
}


bool UXAttrributeComponent::IsAlive()
{
	return healthy > 0.0;
}

bool UXAttrributeComponent::IsActorLive(AActor* Actor)
{
	if(Actor == nullptr)
	{
		return false;
	}
	UXAttrributeComponent* Attribute = Cast<UXAttrributeComponent>(Actor->GetComponentByClass(UXAttrributeComponent::StaticClass()));
	if(Attribute)
	{
		return Attribute->IsAlive();
	}
	return false;
}


bool UXAttrributeComponent::AlterHealthy(AActor* Instor,float delt)
{
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}
	float OldHealthy = healthy;
	float NewHealthy = FMath::Clamp(healthy + delt,0.0,MaxHealthy);
	float ActualDelta = NewHealthy - OldHealthy;
	UE_LOG(LogTemp,Log,TEXT("Ower:%s is %d"),*GetOwner()->GetName(),GetOwner()->HasAuthority());
	if(GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp,Log,TEXT("%s -> %s"),*Instor->GetName(),*GetOwner()->GetName());
		healthy = NewHealthy;
	
		//healthyChange.Broadcast(Instor, this, healthy, ActualDelta);
		if(ActualDelta != 0)
		{
			healthyChange.Broadcast(Instor, this, healthy, ActualDelta);
			//MulticastHealthChanged(Instor,healthy,ActualDelta);
		}
		
		if(healthy == 0 && ActualDelta <0)
		{
			AXGameMode* Gme = GetWorld()->GetAuthGameMode<AXGameMode>();
			if(Gme)
			{
				Gme->ActorOnKilled(GetOwner(),Instor);
			}
		}
	}
	
	return ActualDelta != 0;
}

float UXAttrributeComponent::GetHealthy()
{
	return  healthy;
}

float UXAttrributeComponent::GetMaxHealthy()
{
	return  MaxHealthy;
}

bool UXAttrributeComponent::isFullHealthy()
{
	return MaxHealthy == healthy;
}


// void UXAttrributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
// {
// 	//UE_LOG(LogTemp,Log,TEXT("%s:%f"),*InstigatorActor->GetName(),healthy);
// 	healthyChange.Broadcast(InstigatorActor,this,healthy,Delta);
// 	UE_LOG(LogTemp,Log,TEXT("%s:%f"),*InstigatorActor->GetName(),healthy);
// }


 void UXAttrributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
 {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UXAttrributeComponent,healthy);
	DOREPLIFETIME(UXAttrributeComponent,MaxHealthy);
	//DOREPLIFETIME_CONDITION(UXAttrributeComponent,MaxHealthy,COND_InitialOnly);
}

void UXAttrributeComponent::OnRep_CurrentHealth(float oldhealthy)
{
	float NewHealthy = FMath::Clamp(healthy,0.0,MaxHealthy);
	float ActualDelta = NewHealthy - oldhealthy;
	if(ActualDelta)
	{
		healthyChange.Broadcast(GetOwner(),this,NewHealthy,NewHealthy - oldhealthy);
	}
	
}


// void UXAttrributeComponent::ServerAlterHealthy_Implementation(AActor* Instagtor, float delt)
// {
// 	if (!GetOwner()->CanBeDamaged())
// 	{
// 		return;
// 	}
// 	float OldHealthy = healthy;
// 	healthy = FMath::Clamp(healthy + delt,0.0,MaxHealthy);
// 	float ActualDelta = healthy - OldHealthy;
//
// 	//healthyChange.Broadcast(Instor, this, healthy, ActualDelta);
// 	if(ActualDelta != 0)
// 	{
// 		MulticastHealthChanged(Instagtor,healthy,ActualDelta);
// 	}
// 	if(healthy == 0 && ActualDelta <0)
// 	{
// 		AXGameMode* Gme = GetWorld()->GetAuthGameMode<AXGameMode>();
// 		if(Gme)
// 		{
// 			Gme->ActorOnKilled(GetOwner(),Instagtor);
// 		}
// 	}
// }





