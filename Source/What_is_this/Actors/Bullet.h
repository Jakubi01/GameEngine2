// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class AWTFPlayer;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class WHAT_IS_THIS_API ABullet : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY()
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY()
	TWeakObjectPtr<AWTFPlayer> CachedPlayer;

	float LifeSpan = 10.f;
	
public:	
	ABullet();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnComponentOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);
};
