// Fill out your copyright notice in the Description page of Project Settings.


#include "XFloatActor.h"

// Sets default values
AXFloatActor::AXFloatActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	// static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsseet(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	//
	// if (CubeVisualAsseet.Succeeded()) {
	// 	VisualMesh->SetStaticMesh(CubeVisualAsseet.Object);
	// 	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	// }

}

// Called when the game starts or when spawned
void AXFloatActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXFloatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLoction = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float Runningtime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(Runningtime - DeltaTime) - FMath::Sin(Runningtime));
	NewLoction.Z += DeltaHeight * 20.0f;
	float DeltaRotation = DeltaTime * 20.0f;
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLoction, NewRotation);

}

