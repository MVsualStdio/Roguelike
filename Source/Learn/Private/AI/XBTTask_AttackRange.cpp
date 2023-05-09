// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XBTTask_AttackRange.h"

#include "AIController.h"
#include "XAttrributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UXBTTask_AttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIControl = OwnerComp.GetAIOwner();
	if(AIControl)
	{
		ACharacter* Ower = Cast<ACharacter>(AIControl->GetPawn());
		if(Ower == nullptr)
		{
			return EBTNodeResult::Type::Failed;
		}

		
		FVector handr = Ower->GetMesh()->GetSocketLocation("hand_r");
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if(!UXAttrributeComponent::IsActorLive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}
		FVector Location = TargetActor->GetActorLocation() - handr;
		FRotator Rotator = Location.Rotation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = Ower;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* Projectile = GetWorld()->SpawnActor<AXProjectileBase>(ProjectileClass,handr,Rotator,SpawnParameters);
		return Projectile?EBTNodeResult::Succeeded:EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
