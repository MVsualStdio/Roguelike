// Fill out your copyright notice in the Description page of Project Settings.


#include "XAction_Projectile.h"

#include <string>
#include <GameFramework/Character.h>

#include "XBlueprintFunctionLibrary.h"

UXAction_Projectile::UXAction_Projectile()
{
	HandSocketName = "hand_r";
	AttackAnimDelay = 0.2f;
}

void UXAction_Projectile::StartAction_Implementation(AActor* Actor)
{
	
	Super::StartAction_Implementation(Actor);
	ACharacter* Character = Cast<ACharacter>(Actor);
	
	if(Character)
	{
		Character->PlayAnimMontage(this->AttackAnim);
		if(Character->HasAuthority())
		{
			FTimerHandle InOutHandle;
            FTimerDelegate Delegate;
            Delegate.BindUFunction(this,"SpawnProjectile",Character);
            GetWorld()->GetTimerManager().SetTimer(InOutHandle,Delegate,AttackAnimDelay,false);
		}

	}
}

void UXAction_Projectile::SpawnProjectile(ACharacter* Character)
{
	if(Spawn && Character)
	{
		FVector handR = Character->GetMesh()->GetSocketLocation(HandSocketName);
		//auto Rote =  GetControlRotation();
		//FindLookAtRotation(handR,);
	
		FVector start = Character->GetPawnViewLocation();
		// CameraComp->GetComponentRotation().Vector()
		FVector end = start +  Character->GetControlRotation().Vector() * 5000;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Character;

		FHitResult OutHit;
		FCollisionObjectQueryParams parameters;
		FCollisionShape shape;
		shape.SetSphere(20.0f);
		parameters.AddObjectTypesToQuery(ECC_WorldStatic);
		bool block = GetWorld()->SweepSingleByObjectType(OutHit, start, end, FQuat::Identity, parameters, shape);

		if (block) {
			end = OutHit.ImpactPoint;
		}
		
		FRotator rotator = FRotationMatrix::MakeFromX(end - handR).Rotator();
		FTransform SpawnTM(rotator, handR);
		GetWorld()->SpawnActor<AActor>(Spawn, SpawnTM, SpawnParams);
		
		// FRotator Rotator =  rotator - Character->GetMesh()->GetComponentRotation();
		// if(Rotator.Yaw < -60)
		// {
		// 	Character->SetActorRotation(rotator);
		// }
		// UXBlueprintFunctionLibrary::Debug(FString("%f",D));
		//UE_LOG(LogTemp,Log,TEXT("throttle %f"), D);
	}
	
	StopAction(Character);
}

void UXAction_Projectile::StopAction_Implementation(AActor* Actor)
{
	Super::StopAction_Implementation(Actor);
}


