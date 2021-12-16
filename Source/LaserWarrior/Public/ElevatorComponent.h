// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ElevatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UElevatorComponent : public UActorComponent
{
	GENERATED_BODY()
	float OriginalHeight;

	UProjectileMovementComponent* MovementComponent;
	bool LastRunStat;

	float OriHeight;
	
public:	
	// Sets default values for this component's properties
	UElevatorComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool RunStatus;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMovementComponent(UProjectileMovementComponent* InMovement);
		
};


