// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WTFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WHAT_IS_THIS_API UWTFGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UWTFGameInstance();

	virtual void Init() override;

	UPROPERTY()
	int32 HighScore = 0;

public:
	UFUNCTION(BlueprintCallable)
	void SetHighScore(const int32 newScore)
	{
		if (newScore > HighScore)
		{
			HighScore = newScore;
		}
	}

	UFUNCTION(BlueprintCallable)
	int32 GetHighScore() const
	{
		if (HighScore <= 0)
			return 0;
		
		return HighScore;
	}
};
