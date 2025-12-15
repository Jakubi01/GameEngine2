// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class WHAT_IS_THIS_API UTextWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text;

public:
	void SetText(const FText& InText) const;
};
