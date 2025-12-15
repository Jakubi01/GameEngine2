// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "What_is_this/Character/WTFEnemy.h"
#include "What_is_this/Character/WTFPlayer.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SetRootComponent(MeshComponent);
	MeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	MeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentOverlap);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->InitialSpeed = 700.f;
	ProjectileMovementComponent->MaxSpeed = 700.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	if (!CachedPlayer.Get())
	{
		CachedPlayer = Cast<AWTFPlayer>(Owner);
	}
	
	SetLifeSpan(LifeSpan);
}

void ABullet::OnComponentOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	AWTFEnemy* Enemy = Cast<AWTFEnemy>(OtherActor);
	if (!Enemy)
		return;
	
	CachedPlayer.Get()->SetPoint(Enemy->GetPoint());
	Enemy->DestroyEnemy();
	this->Destroy();
}
