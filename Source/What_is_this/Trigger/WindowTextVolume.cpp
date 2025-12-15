// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowTextVolume.h"

#include "What_is_this/Widget/TextWidget.h"
#include "What_is_this/Widget/TextWidgetComponent.h"
#include "Components/BrushComponent.h"

AWindowTextVolume::AWindowTextVolume()
{
	GetBrushComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlapEvent);
	GetBrushComponent()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlapEvent);

	TextWidgetComponent = CreateDefaultSubobject<UTextWidgetComponent>(TEXT("Text Widget Component"));
	TextWidgetComponent->SetupAttachment(GetBrushComponent());
}

void AWindowTextVolume::BeginPlay()
{
	Super::BeginPlay();
	
	if (TextWidgetComponent)
	{
		TextWidgetComponent->SetRelativeLocation(this->GetBounds().Origin);
		TextWidgetComponent->SetRelativeRotation(this->GetActorRotation());
		
		TextWidget = Cast<UTextWidget>(TextWidgetComponent->GetUserWidgetObject());
		if (TextWidget)
		{
			TextWidget->SetVisibility(ESlateVisibility::Collapsed);

			switch (TextType)
			{
			case ETextType::ETT_Door:
				TextWidget->SetText(FText::FromString("Door"));
				break;
				
			case ETextType::ETT_Window:
				TextWidget->SetText(FText::FromString("Window"));
				break;
				
			case ETextType::ETT_MAX:
				TextWidget->SetText(FText::FromString("NONE"));
				break;
				
			default:
				break;
			}
		}
	}
}

void AWindowTextVolume::OnBeginOverlapEvent(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (TextWidget)
	{
		TextWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AWindowTextVolume::OnEndOverlapEvent(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (TextWidget)
	{
		TextWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
