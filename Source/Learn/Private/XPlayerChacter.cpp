// Fill out your copyright notice in the Description page of Project Settings.


#include "XPlayerChacter.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Math\RotationMatrix.h>
#include "XAMsgicProjectile.h"
#include "XGameInterface.h"
#include "XUInterActorComponent.h"
#include "XAttrributeComponent.h"
#include "XActionActorComponent.h"
#include "XBlueprintFunctionLibrary.h"

// Sets default values
AXPlayerChacter::AXPlayerChacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bInheritRoll = true;
	SpringArmComp->bInheritPitch = true;
	SpringArmComp->bInheritYaw = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	
	ActorComp = CreateDefaultSubobject<UXUInterActorComponent>("ActorComp");
	AttributeComp = CreateDefaultSubobject<UXAttrributeComponent>("AttributeComp");
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	ActionComp = CreateDefaultSubobject<UXActionActorComponent>("ActionComp");
	
}

void AXPlayerChacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->healthyChange.AddDynamic(this,&AXPlayerChacter::OnHealthyChanges);
	//.AddDynamic(this,&AXPlayerChacter::OnHealthyChanges);
//
	//ActionComp->AddAction(Sprint);
	// ActionComp->AddAction(Sprint);
}



// Called when the game starts or when spawned
void AXPlayerChacter::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void AXPlayerChacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AXPlayerChacter::Forward(float value) {
	auto ControlRoute =  GetControlRotation();
	ControlRoute.Pitch = 0.0f;
	ControlRoute.Roll = 0.0f;
	AddMovementInput(ControlRoute.Vector(), value);
	//AddMovementInput(GetActorForwardVector(), value);
}

void AXPlayerChacter::MoveLeftorRight(float value) {
	auto ControlRoute = GetControlRotation();
	ControlRoute.Pitch = 0.0f;
	ControlRoute.Roll = 0.0f;
	FVector rightVecotr = FRotationMatrix(ControlRoute).GetScaledAxis(EAxis::Y);

	AddMovementInput(rightVecotr, value);
	//AddMovementInput(GetActorRightVector(), value);
}

void AXPlayerChacter::Jump() {
	Super::bPressedJump = true;
}
void AXPlayerChacter::Look(float value) {
	Super::AddControllerPitchInput(value);
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Y"));
	//}
}



void AXPlayerChacter::OpenBox()
{
	if (ActorComp) {
		ActorComp->PrimaryInterAct();
	}
	
}

FVector AXPlayerChacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}


// Called to bind functionality to input
void AXPlayerChacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AXPlayerChacter::Forward);
	PlayerInputComponent->BindAxis("MoveLeftorRight", this, &AXPlayerChacter::MoveLeftorRight);
	PlayerInputComponent->BindAxis("Turn", this, &AXPlayerChacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look", this, &AXPlayerChacter::Look);
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &AXPlayerChacter::Jump);
	PlayerInputComponent->BindAction("Open", IE_Pressed, this, &AXPlayerChacter::OpenBox);
	PlayerInputComponent->BindAction("Spring", IE_Pressed, this, &AXPlayerChacter::SprintRuning);
	PlayerInputComponent->BindAction("Spring", IE_Released, this, &AXPlayerChacter::SprintStopRuning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AXPlayerChacter::ProjectileAttack);
	PlayerInputComponent->BindAction("Parry", IE_Pressed, this, &AXPlayerChacter::StartParry);
}




void AXPlayerChacter::OnHealthyChanges(AActor* Actor, UXAttrributeComponent* ownComp, float Healthy, float Delt)
{
	
	if(Delt < 0.0f && Healthy <= 0.0f)
	{
		APlayerController* PC =Cast<APlayerController>( GetController());
		DisableInput(PC);
		SetActorEnableCollision(false);
		SetLifeSpan(10.0f);
		//SetActorEnableCollision(true);
		//OnDeath.Broadcast();
		// Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

void AXPlayerChacter::SprintRuning()
{
	ActionComp->StartActionByName(this,"Sprint");
	
}

void AXPlayerChacter::SprintStopRuning()
{
	ActionComp->StopActionByName(this,"Sprint");
}

void AXPlayerChacter::ProjectileAttack()
{
	
	ActionComp->StartActionByName(this,"Attack");
}

void AXPlayerChacter::StartParry()
{
	UXBlueprintFunctionLibrary::Debug("Attack");
	ActionComp->StartActionByName(this,"Parry");
}
