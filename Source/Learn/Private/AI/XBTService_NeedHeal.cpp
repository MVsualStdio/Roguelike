// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XBTService_NeedHeal.h"

#include "AIController.h"
#include "AI/XAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void UXBTService_NeedHeal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackComp= OwnerComp.GetBlackboardComponent();
	AAIController* AIController  =  OwnerComp.GetAIOwner();
	ACharacter* AI =  Cast<ACharacter>(AIController->GetPawn());
	if(AI)
	{
		UXAttrributeComponent* AttributeComp = Cast<UXAttrributeComponent>(AI->GetComponentByClass(UXAttrributeComponent::StaticClass()));
		if(AttributeComp)
		{
			float rate = AttributeComp->GetHealthy() / AttributeComp->GetMaxHealthy();

			BlackComp->SetValueAsBool(NeedHealKey.SelectedKeyName,rate<=0.4f);
			
		}
	}
}
