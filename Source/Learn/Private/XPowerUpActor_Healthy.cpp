// Fill out your copyright notice in the Description page of Project Settings.


#include "XPowerUpActor_Healthy.h"

#include "XAttrributeComponent.h"
#include "XPlayerState.h"


AXPowerUpActor_Healthy::AXPowerUpActor_Healthy()
{
	CreaitsCost = 30;
}


void AXPowerUpActor_Healthy::interactGet_Implementation(APawn* Pawn)
{
	// AActor* Ower =  GetOwner();
	UXAttrributeComponent* Attribute= Cast<UXAttrributeComponent>(Pawn->GetComponentByClass(UXAttrributeComponent::StaticClass()));
	if(Attribute && isVisable)
	{
		AXPlayerState* State = Cast<AXPlayerState>(Pawn->GetPlayerState<AXPlayerState>());
		if(State)
		{
			if(State->RemoveCredites(CreaitsCost))
			{
				float healthy = Attribute->GetHealthy();
                Attribute->AlterHealthy(Pawn,CreateHealthy);
                Hiden();
			}
			
		}

	}
	
}

FText AXPowerUpActor_Healthy::GetInteractText_Implementation(APawn* Pawn)
{
	UXAttrributeComponent* Attribute= Cast<UXAttrributeComponent>(Pawn->GetComponentByClass(UXAttrributeComponent::StaticClass()));
	if(Attribute && isVisable && Attribute->isFullHealthy())
	{
		return NSLOCTEXT("IntergetActor","Haalthy_Warring","Healthy is Full");
	}
	return FText::Format(NSLOCTEXT("IntergetActor","Haalthy_Message","Cost {0} Credits"),CreaitsCost);
}
