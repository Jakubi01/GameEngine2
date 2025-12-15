// Fill out your copyright notice in the Description page of Project Settings.


#include "WTFBlueprintFunctionLibrary.h"

#include "What_is_this/Character/WTFEnemy.h"
#include "Kismet/GameplayStatics.h"

void UWTFBlueprintFunctionLibrary::DestroyAllEnemyObject(UObject* WorldContextObject)
{
	if (!WorldContextObject)
		return;

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AWTFEnemy::StaticClass(), OutActors);

	if (OutActors.IsEmpty())
		return;

	for (AActor* Actor : OutActors)
	{
		if (Actor->HasAllFlags(RF_BeginDestroyed))
			continue;
		
		Actor->Destroy();
	}
}
