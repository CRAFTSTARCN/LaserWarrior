// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Hitable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHitable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LASERWARRIOR_API IHitable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, Category="HitCallback")
	float GetHit(AActor* Hitter, const FHitResult& Hit, float AtkDamage);
};
