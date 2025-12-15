// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "What_is_this/What_is_thisGameMode.h"
#include "What_is_this/Character/WTFEnemy.h"

AEnemySpawner::AEnemySpawner()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	int32 offset = -(Offset * (SpawnerCounts / 2));

	for (int32 i = 0; i < SpawnerCounts; i++)
	{
		FName LocName = FName("SpawnLocation" + FString::FromInt(i));
		USceneComponent* SpawnLocation = NewObject<USceneComponent>(this, LocName);
		SpawnLocation->SetupAttachment(Root);
		SpawnLocation->RegisterComponent();
		SpawnLocation->SetRelativeLocation(FVector(1000, offset, 0));
		SpawnLocation->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
		offset += Offset;
		SpawnLocations.AddUnique(SpawnLocation);
	}

	UWorld* world = GetWorld();
	if (!world)
		return;
	
	WTFGameMode = Cast<AWhat_is_thisGameMode>(world->GetAuthGameMode());

	world->GetTimerManager().SetTimer(
			SpawnTimer,
			[this, world]()->void
			{
				if (WTFGameMode.Get()->GetIsGameOver())
				{
					world->GetTimerManager().ClearTimer(SpawnTimer);
					return;
				}

				SpawnEnemy(world);
			},
			SpawnRate,
			true
		);
}

void AEnemySpawner::EndPlay(EEndPlayReason::Type Reason)
{
	if (UWorld* World = GetWorld())
		World->GetTimerManager().ClearTimer(SpawnTimer);
		
	Super::EndPlay(Reason);
}

void AEnemySpawner::SpawnEnemy(UWorld* world)
{
	if (!EnemyClass || WTFGameMode.Get()->GetIsGameOver())
		return;

	const ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!player)
		return;

	for (const auto& spawnLocation : SpawnLocations)
	{
		const bool spawnable = FMath::RandBool();
		if (!spawnable)
			continue;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const FVector Location = spawnLocation->GetComponentLocation();
		const FRotator Rotation = spawnLocation->GetComponentRotation();

		const AWTFEnemy* SpawnedEnemy = world->SpawnActor<AWTFEnemy>(EnemyClass, Location, Rotation, SpawnParams);
		if (!SpawnedEnemy)
			continue;
		
		SpawnedEnemy->SetProjectileDirection((player->GetActorLocation() - SpawnedEnemy->GetActorLocation()).GetSafeNormal());
	}
}
