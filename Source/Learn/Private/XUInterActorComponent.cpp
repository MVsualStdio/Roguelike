// Fill out your copyright notice in the Description page of Project Settings.


#include "XUInterActorComponent.h"

#include "XBlueprintFunctionLibrary.h"
#include "XPowerUpActor.h"
#include "XWorldMyUserWidget.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UXUInterActorComponent::UXUInterActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UXUInterActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UXUInterActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn->IsLocallyControlled())
	{
		FindInteract();
	}
	
	// ...
}

void UXUInterActorComponent::PrimaryInterAct()
{
	//FHitResult OutHit;
	ServerInteract(ForceActor);
	
}

void UXUInterActorComponent::FindInteract()
{
	FVector End;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	FVector Start;
	AActor* ower =  GetOwner();
	FRotator route;
	ower->GetActorEyesViewPoint(Start, route);

	End = Start + route.Vector() * 1000;

	//GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, ObjectQueryParams);
	TArray<FHitResult>  OutHits;
	FCollisionShape shape;
	shape.SetSphere(30.0f);
	bool blockHit = GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, ObjectQueryParams, shape);
	for (auto OutHit : OutHits) {
		AActor* HitActor =  OutHit.GetActor();
		if (HitActor) {
			if(HitActor->Implements<UXGameInterface>()) {
				APawn* pawn = Cast<APawn>(ower);
				ForceActor = HitActor;
				break;
			}
		}
	}
	if(ForceActor)
	{
		if(!ForceActor->IsHidden())
		{
			if(UI == nullptr && UserWidgetClass)
			{
				UI = CreateWidget<UXWorldMyUserWidget>(GetWorld(),UserWidgetClass);
			
			}
			if(UI)
			{
			
				UI->AttachActor = ForceActor;
				if(UI && !UI->IsInViewport())
				{
					UI->AddToViewport();
				}
			}
		}
	}
	else
	{
		if (UI)
		{
			UI->RemoveFromParent();
		}
	}
}


void UXUInterActorComponent::ServerInteract_Implementation(AActor* Infocus)
{
	if(Infocus == nullptr)
	{
		return;
	}
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IXGameInterface::Execute_interactGet(Infocus, MyPawn);;
}
