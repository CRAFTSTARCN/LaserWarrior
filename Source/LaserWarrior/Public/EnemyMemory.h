// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMemory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UEnemyMemory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMemory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool PlayerInSight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool PlayerInAbsoluteRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool PlayerInMemoryRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool PlayerIsRemembered;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ForgetAll();

	UFUNCTION(BlueprintCallable)
	void PlayerEnterSight();

	UFUNCTION(BlueprintCallable)
	void PlayerOutSight();

	UFUNCTION(BlueprintCallable)
	void PlayerEnterAbsoluteRange();

	UFUNCTION(BlueprintCallable)
	void PlayerOutAbsoluteRange();

	UFUNCTION(BlueprintCallable)
	void PlayerEnterMemoryRange();

	UFUNCTION(BlueprintCallable)
	void PlayerOutMemoryRange();

	UFUNCTION(BlueprintCallable)
	bool EnemyActivated() const;
};
