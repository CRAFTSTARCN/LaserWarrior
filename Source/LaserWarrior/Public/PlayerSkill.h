// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerSkill.generated.h"

UCLASS()
class LASERWARRIOR_API APlayerSkill : public AActor
{
	GENERATED_BODY()

	float TimeCounter;
	
public:	
	// Sets default values for this actor's properties
	APlayerSkill();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CarryDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* DamageBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnHitEnemy(AEnemy* HittedEnemy, const FHitResult& Hit);
};
