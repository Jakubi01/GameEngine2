// Copyright Epic Games, Inc. All Rights Reserved.

#include "What_is_thisGameMode.h"
#include "What_is_thisCharacter.h"
#include "UObject/ConstructorHelpers.h"

float AWhat_is_thisGameMode::EnemySpeed = 300.f;

AWhat_is_thisGameMode::AWhat_is_thisGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
