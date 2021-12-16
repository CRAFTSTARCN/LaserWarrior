// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attacker.h"
#include "CharacterData.h"
#include "GameFramework/Character.h"
#include "LaserWarrior/Hitable.h"
#include "Enemy.generated.h"

class AEnemyControllerCPP;

UCLASS()
class LASERWARRIOR_API AEnemy : public ACharacter, public IHitable, public IAttacker
{
	GENERATED_BODY()
	
	AEnemyControllerCPP* SelfController;

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCharacterData* EnemyData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ContainsScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ContainsExp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ExpIncreaseRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalAttackStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackStage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bEndure;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsBeingHitted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRandomStream RandomStream;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<float, TSubclassOf<AActor>> DropTable;
	
	UFUNCTION(BlueprintImplementableEvent)
	float PlayAttackAnime(int32 Stage);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHittedAnime();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void ReduceHealth(float Value, AActor* CausedBy);

	UFUNCTION(BlueprintCallable)
	virtual void InitWithLevel(int32 InLevel);

	UFUNCTION(BlueprintCallable)
	virtual void SetUpStateInfo();

	UFUNCTION(BlueprintCallable)
	virtual void Drop();

	UFUNCTION(BlueprintCallable)
	float Attack();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealthLimit() const { return EnemyData->HealthLimit; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetContentScore() const { return ContainsScore; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetContentExp() const { return ContainsExp; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetEnemyLevel() const { return EnemyData->Level; }
	
	UFUNCTION(BlueprintNativeEvent)
	void EnemyFallDown();

	virtual float DealAttackDamage_Implementation(AActor* Hitted, const FHitResult& HitResult) override;
	virtual float GetHit_Implementation(AActor* Hitter, const FHitResult& Hit, float AtkDamage) override;
	virtual void EnemyFallDown_Implementation();

};
