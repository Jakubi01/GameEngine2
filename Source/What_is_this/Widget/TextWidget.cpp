// Fill out your copyright notice in the Description page of Project Settings.


#include "TextWidget.h"
#include "Components/TextBlock.h"

void UTextWidget::SetText(const FText& InText) const
{
	if (InText.IsEmpty())
		return;

	Text->SetText(InText);
}
