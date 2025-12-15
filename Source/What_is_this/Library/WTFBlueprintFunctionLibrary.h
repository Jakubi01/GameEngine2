// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WTFBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class WHAT_IS_THIS_API UWTFBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void DestroyAllEnemyObject(UObject* WorldContextObject);
};
