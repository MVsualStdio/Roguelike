// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XAICharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "GameDelegates.h"
#include "XActionActorComponent.h"
#include "XBlueprintFunctionLibrary.h"
#include "XWorldMyUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AXAICharacter::AXAICharacter()
{
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>("SensingComp");
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AttributeComp = CreateDefaultSubobject<UXAttrributeComponent>("AttributeComp");
	ActionComp =CreateDefaultSubobject<UXActionActorComponent>("ActionComp");
	ParHitMa = "HitTime";
}

void AXAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SensingComp->OnSeePawn.AddDynamic(this,&AXAICharacter::OnSence);
	AttributeComp->healthyChange.AddDynamic(this,&AXAICharacter::OnHealthyChanges);
}



void AXAICharacter::OnSence(APawn* Pawn)
{
	
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);
		UXWorldMyUserWidget* Widget = CreateWidget<UXWorldMyUserWidget>(GetWorld(), WorldClass);
		if(Widget)
		{
			Widget->AttachActor = this;
			// Index of 10 (or anything higher than default of 0) places this on top of any other widget.
			// May end up behind the minion health bar otherwise.
			Widget->AddToViewport(10);
			FTimerHandle Handle;
			FTimerDelegate Delegate;
			Delegate.BindLambda([Widget]()
			{
				Widget->RemoveFromParent();
			});
			GetWorld()->GetTimerManager().SetTimer(Handle,Delegate,5,false);
			
		}
	}
	
	
	
}

void AXAICharacter::SetTargetActor(AActor* Actor)
{
	AAIController* AIControl =  Cast<AAIController>(GetController());
	
	if(AIControl)
	{
		UBlackboardComponent* BBComp = AIControl->GetBlackboardComponent();
		BBComp->SetValueAsObject("TargetActor",Actor);
	}

}

AActor* AXAICharacter::GetTargetActor()
{
	AAIController* AIControl =  Cast<AAIController>(GetController());
	
	if(AIControl)
	{
		UBlackboardComponent* BBComp = AIControl->GetBlackboardComponent();
		return Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
	}
	return nullptr;
}


void AXAICharacter::OnHealthyChanges(AActor* Actor, UXAttrributeComponent* ownComp, float Healthy, float Delt)
{
	
	if(Delt < 0.0f )
	{
		GetMesh()->SetScalarParameterValueOnMaterials(ParHitMa,GetWorld()->TimeSeconds);
		if(Actor != this)
		{
			SetTargetActor(Actor);
		}
		if(WorldWidget == nullptr)
		{
			WorldWidget = CreateWidget<UXWorldMyUserWidget>(GetWorld(),HealthyWidget);
            if(WorldWidget)
            {
            	WorldWidget->AttachActor = this;
            	WorldWidget->AddToViewport();
            }
		}

		if(Healthy <= 0.0f)
		{
			AAIController* AI =Cast<AAIController>( GetController());
			if(AI)
			{
				AI->GetBrainComponent()->StopLogic("Killed");
			}
			
			//GetMesh()->SetSimulatePhysics(true);
			//GetMesh()->SetCollisionProfileName("Ragdoll");
			SetActorEnableCollision(false);
			GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
            

			SetLifeSpan(10.0f);
			
            // Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            // Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
			// FTimerHandle TimerHandle;
			// GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AXAICharacter::RemoveFromRoot(),5.0f);
		}
	}
}

// void AXAICharacter::ToDestroy()
// {
// 	AXAICharacter::Destroy();
// }
