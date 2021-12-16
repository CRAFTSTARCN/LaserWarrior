// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterData.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UCharacterData : public UActorComponent
{
	GENERATED_BODY()

	float CalGap(float Data, float DataTop);
	
public:	
	// Sets default values for this component's properties
	UCharacterData();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 LevelLimit;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float HealthLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float ManaLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float ManaLimitTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float HealthLimitTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float Atk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float AtkTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float DefenceTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float CriticalRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float CriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float NeedUpgradeExp;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Data")
	float ExpIncreaseRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentExp;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void Upgrade();
};
