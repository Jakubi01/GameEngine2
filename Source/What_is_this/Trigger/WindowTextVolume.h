// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "WindowTextVolume.generated.h"

class UTextWidgetComponent;
class UTextWidget;

UENUM()
enum class ETextType : uint8
{
	ETT_Door	UMETA(DisplayName = "Door"),
	ETT_Window	UMETA(DisplayName = "Window"),
	ETT_MAX		UMETA(DisplayName = "MAX")
};

/**
 * 
 */
UCLASS()
class WHAT_IS_THIS_API AWindowTextVolume : public AVolume
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Option)
	TObjectPtr<UTextWidgetComponent> TextWidgetComponent;
	
	UPROPERTY()
	TObjectPtr<UTextWidget> TextWidget;

	UPROPERTY(EditAnywhere, Category = Option)
	ETextType TextType;

protected:
	UFUNCTION()
	virtual void OnBeginOverlapEvent(UPrimitiveComponent* OverlapComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

	UFUNCTION()
	virtual void OnEndOverlapEvent(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AWindowTextVolume();

	virtual void BeginPlay() override;
};