// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LaserWarrior/ARPGPlayerController.h"
#include "PlayerStatusUICpp.generated.h"

/**
 * 
 */
UCLASS()
class LASERWARRIOR_API UPlayerStatusUICpp : public UUserWidget
{
	GENERATED_BODY()

	float LastHeathPercentage;

	AARPGPlayerController* PlayerController;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HealthTop;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DodgeCoolDownPercentage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PlayerScore;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SkillCoolDownPercentage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	float ExpPercentage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlayerLifeRemain;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlayerLevel;
	
public:

	UFUNCTION(BlueprintCallable)
	void SetUpPlayerController(AARPGPlayerController* InController);
	
	UFUNCTION(BlueprintCallable)
	float SetUpHealthInfo();

	UFUNCTION(BlueprintCallable)
	float SetManaInfo();

	UFUNCTION(BlueprintCallable)
	void SetUpCoolDownInfo();

	UFUNCTION(BlueprintCallable)
	void SetUpScore();

	UFUNCTION(BlueprintCallable)
	void SetupExp();

	UFUNCTION(BlueprintCallable)
	void SetUpLife();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeHpColor(float HealthPercentage);
};
