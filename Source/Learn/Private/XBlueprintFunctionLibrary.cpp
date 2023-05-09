// Fill out your copyright notice in the Description page of Project Settings.


#include "XBlueprintFunctionLibrary.h"

#include "XAttrributeComponent.h"

bool UXBlueprintFunctionLibrary::ApplyDamage(AActor* DamageActor, AActor* TargetActor, float Damage)
{
	UXAttrributeComponent* AttributeComp = Cast<UXAttrributeComponent>(DamageActor->GetComponentByClass(UXAttrributeComponent::StaticClass()));
	if(AttributeComp)
	{
		return AttributeComp->AlterHealthy(TargetActor,Damage);
	}
	return false;
}


bool UXBlueprintFunctionLibrary::ApplyActorDamage(AActor* DamageActor, AActor* TargetActor, float Damage, const FHitResult& HitResult)
{
	if(ApplyDamage(DamageActor,TargetActor,Damage))
	{
		
		UPrimitiveComponent* PrimitiveComponent = HitResult.GetComponent();
		if(PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics(HitResult.BoneName))
		{
			PrimitiveComponent->AddImpulseAtLocation(-HitResult.ImpactNormal*500000.0f,HitResult.ImpactPoint,HitResult.BoneName);
			return true;
		}
		return true;
	}
	return false;
}

void UXBlueprintFunctionLibrary::Debug(FString Str)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Str);
	}
}
