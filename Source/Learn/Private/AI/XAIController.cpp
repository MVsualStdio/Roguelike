// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


void AXAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(AIBT);

	//  APawn* Ower = UGameplayStatics::GetPlayerPawn(this,0);
	// if(Ower)
	// {
	// 	GetBlackboardComponent()->SetValueAsVector("MoveToLocation",Ower->GetActorLocation());
	// 	
	// 	GetBlackboardComponent()->SetValueAsObject("TargetActor",Ower);
	// }
}
