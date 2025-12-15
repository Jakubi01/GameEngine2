// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "What_is_thisGameMode.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EGameOverState : uint8
{
	Defeat 	UMETA(DisplayName = "Defeat"),
	Win  	UMETA(DisplayName = "Win")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOverDelegate, EGameOverState, state);

UCLASS(minimalapi)
class AWhat_is_thisGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = Option, meta = (AllowPrivateAccess = true))
	bool bGameOver = false;

	UPROPERTY(EditDefaultsOnly, Category = Option)
	int32 GameOverPoint = 300;

public:
	AWhat_is_thisGameMode();

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnGameOverDelegate OnGameOverDelegate;
	
	int32 GetGameOverPoint() const { if (GameOverPoint <= 0) return 0; return GameOverPoint; }

	bool GetIsGameOver() const { return bGameOver; }
	
	static float EnemySpeed; 
};



