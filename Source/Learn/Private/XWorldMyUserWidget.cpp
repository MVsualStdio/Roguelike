// Fill out your copyright notice in the Description page of Project Settings.


#include "XWorldMyUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void UXWorldMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	FVector2D ScreenPosition;
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),AttachActor->GetActorLocation() + WorldOffset,ScreenPosition))
	{
		float Scale =  UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= Scale;
		
		if(ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
