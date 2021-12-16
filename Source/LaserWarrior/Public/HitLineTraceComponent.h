// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitTraceComponent.h"
#include "HitLineTraceComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UHitLineTraceComponent : public UHitTraceComponent
{
	GENERATED_BODY()
	TArray<FName> SocketName;
	TMap<FName, FVector> SocketPosition;

public:

	virtual void InitWeapon(UMeshComponent* InWeaponMesh) override;
	
	virtual void Trace() override;

	virtual void EnableTrace() override;
};
