// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LaserWarrior/PlayerCharacterCPP.h"
#include "BuffPots.generated.h"

UCLASS()
class LASERWARRIOR_API ABuffPots : public AActor
{
	GENERATED_BODY()

	APlayerController* PlayerController;

	float TimeCount;
	
public:	
	// Sets default values for this actor's properties
	ABuffPots();

protected:
	// Called when the game starts or when spawned

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* DefaultRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlayTime;
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnTouchPlayer(APlayerCharacterCPP* Player);
};
