// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WTFPlayer.generated.h"

class UWTFGameInstance;
class AWhat_is_thisGameMode;
class ABullet;

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPointChangedDelegate, int32, point);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, int32, health);
	
UCLASS()
class WHAT_IS_THIS_API AWTFPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Option)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = Option)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "WTF|Option")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "WTF|Option")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "WTF|Option")
	TObjectPtr<UInputAction> IA_FireBullet;

	UPROPERTY(EditDefaultsOnly, Category = "WTF|Option")
	TSubclassOf<ABullet> BulletClass;

	TWeakObjectPtr<AWhat_is_thisGameMode> WTFGameMode;

	UPROPERTY(VisibleAnywhere, Category = "WTF|Condition")
	int32 GamePoint = 0;
	
	UPROPERTY(VisibleAnywhere, Category = "WTF|Condition")
	int32 PlayerHealth = 100;
	
	UPROPERTY(EditAnywhere, Category = "WTF|Condition")
	float XOffset = 300.f;
	
	UPROPERTY(EditAnywhere, Category = "WTF|Option")
	float YOffset = 1000.f;
	
	UPROPERTY(VisibleAnywhere, Category = "WTF|Reference")
	TObjectPtr<AActor> BackGroundActor;

	UPROPERTY(BlueprintAssignable)
	FOnPointChangedDelegate OnPointChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedDelegate OnHealthChangedDelegate;
	
	void Move(const FInputActionValue& Value);
	void FireBullet(const FInputActionValue& Value);

public:
	AWTFPlayer();
	
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void SetPoint(const int32 point);
	void SetHealth(const int32 damage);

	UFUNCTION(BlueprintCallable, Category = Init)
	void InitProperties()
	{
		GamePoint = 0;
		PlayerHealth = 100;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetPoint() const { return FMath::Clamp<int32>(GamePoint, 0, GamePoint);}
	int32 GetHealth() const { return FMath::Clamp<int32>(PlayerHealth, 0, PlayerHealth); }
	
	void ClampPlayerLocation();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
