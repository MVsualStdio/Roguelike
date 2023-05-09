// Fill out your copyright notice in the Description page of Project Settings.


#include "XTargetDummy.h"

#include "XAttrributeComponent.h"


// Sets default values
AXTargetDummy::AXTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	staticComp = CreateDefaultSubobject<UStaticMeshComponent>("staticComp");
	RootComponent =  staticComp;
	AttributeComp = CreateDefaultSubobject<UXAttrributeComponent>("AttriuteComp");
	AttributeComp->healthyChange.AddDynamic(this,&AXTargetDummy::OnHealthyChanges);
}


void AXTargetDummy::OnHealthyChanges(AActor* Actor, UXAttrributeComponent* OwnComp, float Healthy, float Delt)
{
	if(Delt < 0.0f)
	{
		staticComp->SetScalarParameterValueOnMaterials("HitTime",GetWorld()->TimeSeconds);
	}
}



