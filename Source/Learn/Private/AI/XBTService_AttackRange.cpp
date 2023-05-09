// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XBTService_AttackRange.h"

#include "AIController.h"
#include "VectorTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/RendererSettings.h"

void UXBTService_AttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackBoard =  OwnerComp.GetBlackboardComponent();
	AActor* TargetActor  =  Cast<AActor>(BlackBoard->GetValueAsObject("TargetActor"));
	
	if(TargetActor)
	{

		AAIController* AI = OwnerComp.GetAIOwner();
		AActor* AIActor = AI->GetPawn();
		if(AIActor)
		{

			float distance = UE::Geometry::Distance(AIActor->GetActorLocation(),TargetActor->GetActorLocation());
			bool AttackKey =  distance<2000.0f;
			bool bHasLOS = false;
			if(AttackKey)
			{
				bHasLOS = AI->LineOfSightTo(TargetActor);
			}
			
			// if(GEngine)
			// {		
			// 	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Yellow,FString::Printf(TEXT("%d"),bHasLOS));
			// }
				
			
			BlackBoard->SetValueAsBool(AttackRangeKey.SelectedKeyName,(AttackKey && bHasLOS));
		}

	}
}	

