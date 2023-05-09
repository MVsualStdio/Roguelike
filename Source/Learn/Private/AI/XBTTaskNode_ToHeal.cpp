// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XBTTaskNode_ToHeal.h"

#include "AIController.h"
#include "AI/XAICharacter.h"

EBTNodeResult::Type UXBTTaskNode_ToHeal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIControl = OwnerComp.GetAIOwner();
	AActor* AI = Cast<AActor>(AIControl->GetPawn());
	if(AI == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	UXAttrributeComponent* Attribute =  Cast<UXAttrributeComponent>(AI->GetComponentByClass(UXAttrributeComponent::StaticClass()));
	if(Attribute == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	Attribute->AlterHealthy(AI,10.0f);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%f"),Attribute->GetHealthy()));
	}
	return EBTNodeResult::Succeeded;
}
