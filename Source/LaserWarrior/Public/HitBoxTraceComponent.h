// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitTraceComponent.h"
#include "HitBoxTraceComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UHitBoxTraceComponent : public UHitTraceComponent
{
	GENERATED_BODY()

	FVector CenterPos;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxHalfSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoxCenterName;

public:

	UHitBoxTraceComponent();
	
	virtual void InitWeapon(UMeshComponent* InWeaponMesh) override;

	virtual void EnableTrace() override;

	virtual void Trace() override;
};
