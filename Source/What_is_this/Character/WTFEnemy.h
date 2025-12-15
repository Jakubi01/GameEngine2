// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WTFEnemy.generated.h"

class AWhat_is_thisGameMode;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class WHAT_IS_THIS_API AWTFEnemy : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = Option)
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float Speed = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = Option)
	float LifeSpan = 8.f;

	UPROPERTY(EditDefaultsOnly, Category = Option)
	int32 Point = 10;

	UPROPERTY(EditDefaultsOnly, Category = Option)
	int32 Damage = 10;
	
	TWeakObjectPtr<AWhat_is_thisGameMode> WTFGameMode;

	FTimerHandle ParticleTimerHandle;
	
public:
	AWTFEnemy();

	void SetProjectileDirection(const FVector& Direction) const;
	void DestroyEnemy();

	int32 GetPoint() const { return FMath::Clamp<int32>(Point, 0, Point);}

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
