// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Weapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UWeapon : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float Atk;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float AtkTopLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int32 Level;
	
	constexpr static int32 LevelLimit = 90;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual float GetAttack();
};
