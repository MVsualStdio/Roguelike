// Fill out your copyright notice in the Description page of Project Settings.


#include "XASitme.h"

#include "XBlueprintFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AXASitme::AXASitme()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AXASitme::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXASitme::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXASitme::interactGet_Implementation(APawn* Pawn)
{
	LidOpened = !LidOpened;
	OnRep_LidOpened();
	// TargetRotation = 111.0f;
	// LidMesh->SetRelativeRotation(FRotator(TargetRotation,0.0f,0.0f));
}

void AXASitme::OnRep_LidOpened()
{
	TargetRotation = 111.0f;
	float CurrPitch = LidOpened ? TargetRotation : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(CurrPitch,0.0f,0.0f));
}

void AXASitme::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 	DOREPLIFETIME(AXASitme, LidOpened);
}

void AXASitme::IntergetOnLoad_Implementation()
{
 	
	UE_LOG(LogTemp,Log,TEXT("%d"),LidOpened);
	OnRep_LidOpened();
}
