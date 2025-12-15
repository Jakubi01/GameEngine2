// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EnemySpawner.generated.h"

class AWhat_is_thisGameMode;
class AWTFEnemy;
/**
 * 
 */
UCLASS()
class WHAT_IS_THIS_API AEnemySpawner : public AVolume
{
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, Category = Option)
	TArray<USceneComponent*> SpawnLocations;

	UPROPERTY(EditAnywhere, Category = Option)
	TSubclassOf<AWTFEnemy> EnemyClass;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, Category = Option)
	float SpawnRate = 1.5f;
	
	UPROPERTY(EditAnywhere, Category = Option)
	int32 SpawnerCounts = 5;
	
	UPROPERTY(EditAnywhere, Category = Option)
	int32 Offset = 1000;

	UPROPERTY()
	TWeakObjectPtr<AWhat_is_thisGameMode> WTFGameMode;
	
	void SpawnEnemy(UWorld* World);
	
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type Reason) override;
};
