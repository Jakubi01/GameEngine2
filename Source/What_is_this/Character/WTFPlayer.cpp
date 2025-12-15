// Fill out your copyright notice in the Description page of Project Settings.


#include "WTFPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "What_is_this/What_is_thisGameMode.h"
#include "What_is_this/Actors/Bullet.h"

AWTFPlayer::AWTFPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->TargetArmLength = 1500.f;
	SpringArmComponent->SetRelativeLocation(FVector(225.f, 0.f, 0.f));
	SpringArmComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	// Default Movement
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->MaxAcceleration = 10000.f;
	GetCharacterMovement()->JumpZVelocity = 0.f;
	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->AirControlBoostMultiplier = 0.f;
}

void AWTFPlayer::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AWTFPlayer::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* World = GetWorld();
	if (!World)
		return;

	WTFGameMode = Cast<AWhat_is_thisGameMode>(World->GetAuthGameMode());
}

void AWTFPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	ClampPlayerLocation();
}

void AWTFPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(IA_FireBullet, ETriggerEvent::Started, this, &ThisClass::FireBullet);
	}
}

void AWTFPlayer::SetPoint(const int32 point)
{
	GamePoint = FMath::Clamp(GamePoint + point, 0, WTFGameMode.Get()->GetGameOverPoint());
	OnPointChangedDelegate.Broadcast(GamePoint);

	if (GamePoint >= WTFGameMode.Get()->GetGameOverPoint())
	{
		WTFGameMode.Get()->OnGameOverDelegate.Broadcast(EGameOverState::Win);
	}
}

void AWTFPlayer::SetHealth(const int32 damage)
{
	PlayerHealth = FMath::Clamp(PlayerHealth - damage, 0, PlayerHealth);
	OnHealthChangedDelegate.Broadcast(PlayerHealth);

	if (PlayerHealth <= 0)
	{
		WTFGameMode.Get()->OnGameOverDelegate.Broadcast(EGameOverState::Defeat);
	}
}

void AWTFPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWTFPlayer::FireBullet(const FInputActionValue& Value)
{	
	if (!BulletClass)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 200.f;

	world->SpawnActor<ABullet>(BulletClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
}

void AWTFPlayer::ClampPlayerLocation()
{
	FVector Location = GetActorLocation();

	const float MinX = -XOffset;
	const float MaxX = XOffset;
	const float MinY = -YOffset;
	const float MaxY = YOffset;

	Location.X = FMath::Clamp(Location.X, MinX, MaxX);
	Location.Y = FMath::Clamp(Location.Y, MinY, MaxY);

	SetActorLocation(Location);
}