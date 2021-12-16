// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attacker.h"
#include "CharacterData.h"
#include "Weapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacterCPP.generated.h"

class AARPGPlayerController;

UCLASS()
class LASERWARRIOR_API APlayerCharacterCPP : public ACharacter, public IAttacker, public IHitable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent *SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent *FollowedCamera;

	AARPGPlayerController* SelfController;

	int32 CurrentCombo;

	float LastTimeHealthPercentage;


public:
	// Sets default values for this character's properties
	APlayerCharacterCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item")
	UWeapon* PlayerWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent *WeaponMesh;

	UCharacterData* PlayerData;

	UFUNCTION(BlueprintImplementableEvent)
	float AttackAnimPlay(int32 AttackComboNum);

	UFUNCTION(BlueprintImplementableEvent)
	void HeavyAttackAnimPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void HittedAnimePlay();

	UFUNCTION(BlueprintImplementableEvent)
	void SkillAnimePlay();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEndure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInvincible;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRandomStream RandomStream;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PlayerAttack();

	virtual void PlayerHeavyAttack();

	virtual void PlayerUseSkill(float ManaCost);

	FORCEINLINE float GetHealth() const { return Health; }

	FORCEINLINE float GetMana() const { return  Mana; }

	UFUNCTION(BlueprintCallable)
	void ResetAttackCombo(int32 InAttackCombo);

	UFUNCTION(BlueprintCallable)
	void SetUpPlayerData(UCharacterData* InPlayerData);

	UFUNCTION(BlueprintCallable)
	void SetPlayerMana(float InMama);

	UFUNCTION(BlueprintCallable)
	void SetPlayerHealth(float InHealth);

	UFUNCTION(BlueprintCallable)
	void InitController(AARPGPlayerController* InController);

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void AddHealthByPercentage(float Percentage);

	UFUNCTION(BlueprintCallable)
	void AddManaByPercentage(float Percentage);

	UFUNCTION(BlueprintCallable)
	float CalculateSkillDamage();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AARPGPlayerController* GetARPGController() { return SelfController; }

	UFUNCTION(BlueprintNativeEvent)
	void PlayerFall();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeHeartMaterial(float Percentage);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDodgeForward();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDodgeBackward();
	
	virtual void Destroyed() override;

	virtual float DealAttackDamage_Implementation(AActor* Hitted, const FHitResult& HitResult) override;

	virtual float GetHit_Implementation(AActor* Hitter, const FHitResult& Hit, float AtkDamage) override;

	virtual void PlayerFall_Implementation();
};

