// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "EnemyControllerCPP.generated.h"

/**
 * 
 */
UCLASS()
class LASERWARRIOR_API AEnemyControllerCPP : public AAIController
{
	GENERATED_BODY()
	AEnemy* ControlledEnemy;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bReadyAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsAlive;

	
public:

	AEnemyControllerCPP();

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	virtual float OnAttack();

	UFUNCTION(BlueprintCallable)
	virtual void OnEnemyNoHealth(AActor* CausedBy);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool EnemyIsAlive() const { return bIsAlive; }
};
