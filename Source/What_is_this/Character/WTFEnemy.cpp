// Fill out your copyright notice in the Description page of Project Settings.


#include "WTFEnemy.h"

#include "WTFPlayer.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "What_is_this/What_is_thisGameMode.h"

AWTFEnemy::AWTFEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootSceneComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("SkeletalMeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	MeshComponent->SetRelativeScale3D(FVector(3.f));
	MeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	MeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	MeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	MeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentOverlap);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(GetRootComponent());
	ParticleSystemComponent->SetAutoActivate(false);
}

void AWTFEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
	
	UWorld* world = GetWorld();
	if (!world)
		return;
	
	WTFGameMode = Cast<AWhat_is_thisGameMode>(world->GetAuthGameMode());
}

void AWTFEnemy::DestroyEnemy()
{
	if (!ParticleSystemComponent)
		return;

	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleSystemComponent->Activate();
	WTFGameMode.Get()->EnemySpeed *= 1.2f;

	UWorld* world = GetWorld();
	if (!world)
		return;
	
	world->GetTimerManager().SetTimer(
			ParticleTimerHandle,
			[this]()->void
			{
				ParticleSystemComponent->Deactivate();
				GetWorld()->GetTimerManager().ClearTimer(ParticleTimerHandle);
				this->Destroy();
			},
			1.3f,
			false
		);
}

void AWTFEnemy::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWTFPlayer* Player = Cast<AWTFPlayer>(OtherActor);
	if (!Player)
		return;
	
	Player->SetHealth(Damage);
	DestroyEnemy();
}

void AWTFEnemy::SetProjectileDirection(const FVector& Direction) const
{	
	if (!ProjectileMovementComponent)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;
	
	ProjectileMovementComponent->Velocity = Direction * Speed;
}
