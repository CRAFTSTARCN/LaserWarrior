// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LaserWarrior/PlayerCharacterCPP.h"
#include "BulletCPP.generated.h"

UCLASS()
class LASERWARRIOR_API ABulletCPP : public AActor
{
	GENERATED_BODY()

	AEnemy* Shooter;

	float Live;
	
public:	
	// Sets default values for this actor's properties
	ABulletCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* BulletMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCapsuleComponent* DefaultRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetShooter(AEnemy* InShooter);
	
	UFUNCTION(BlueprintCallable)
	void HitCharacter(APlayerCharacterCPP* HittedPlayer, const FHitResult& HitResult);

};
