// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class LASERWARRIOR_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()

	AEnemy* BandedEnemy;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 EnemyLevel;
	
public:
	UEnemyHealthBar(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void InitEnemy(AEnemy* InEnemy);

	UFUNCTION(BlueprintCallable)
	float UpdateHealthPercentage();
};
