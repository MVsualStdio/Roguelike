// Fill out your copyright notice in the Description page of Project Settings.


#include "XPowerUpActor.h"
#include "Net/UnrealNetwork.h"
#include "XAttrributeComponent.h"

// Sets default values
AXPowerUpActor::AXPowerUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);
	CoverTime = 5.0f;
	CreateHealthy = 20.0f;
	bReplicates = true;
	isVisable = true;
}

// Called when the game starts or when spawned
void AXPowerUpActor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AXPowerUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ActorLocation = GetActorLocation();
	FRotator ActorRotaion = GetActorRotation();
	float RunningTime  = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime*3.0 - DeltaTime*3.0) - FMath::Sin(RunningTime*3.0));
	ActorLocation.Z += DeltaHeight * 10.0f;

	SetActorLocation(ActorLocation);
}

void AXPowerUpActor::interactGet_Implementation(APawn* Pawn)
{

}

void AXPowerUpActor::Exist()
{
	isVisable = true;
	SetActorEnableCollision(true);
	MeshComp->SetVisibility(true);

}

void AXPowerUpActor::Hiden()
{
	isVisable = false;
	MeshComp->SetVisibility(false);
	SetActorEnableCollision(false);
	GetWorld()->GetTimerManager().SetTimer(TimeHandle,this,&AXPowerUpActor::Exist,CoverTime);

}

void AXPowerUpActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXPowerUpActor,isVisable)
}

void AXPowerUpActor::OnRep_Hiden()
{
	isVisable ? Exist():Hiden();
}

FText AXPowerUpActor::GetInteractText_Implementation(APawn* Pawn)
{
	return FText::GetEmpty();
}


// bool AXPowerUpActor::IsHinden(AActor* Actor)
// {
// 	if(Actor && Actor->Implements<AXPowerUpActor>())
// 	{
// 		Actor
// 	}
// }



