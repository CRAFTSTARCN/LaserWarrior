// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class LASERWARRIOR_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

	float TotalSecond;

	float LastSpawnTime;

	float SpawnGap;

	APlayerController* TargetPlayerController;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* RangeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int32 CurrentEnemyInRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemyInRangeLimit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentEnemySpawnLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float UpgradeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinSpawnGap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpawnGap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinSpawnDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnemyUpgradeGap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRandomStream RandomStream;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AEnemy>> EnemySpawnedClass;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnRandomPos();

	UFUNCTION(BlueprintCallable)
	virtual bool SpawnAtPosition(float X, float Y);
};
