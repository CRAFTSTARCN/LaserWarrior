// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackDamageScalar.h"
#include "GameFramework/PlayerController.h"
#include "CharacterData.h"
#include "ARPGPlayerController.generated.h"

/**
 * 
 */

class APlayerCharacterCPP;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDiedEvent);


UCLASS()
class LASERWARRIOR_API AARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	APlayerCharacterCPP* PlayerCharacter;
	void DecreaceCoolDown(float& CoolDown, float Delta);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCharacterData* PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAttackDamageScalar* ScalarSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LifeRemain;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnPlayerDiedEvent OnPlayerDiedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bReadyToAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPlayerFallDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	bool bAllowDodge;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DodgeCooldownCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DodgeCooldownLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillManaRequire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillCoolDownCurrent;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillCoolDownLimit;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Score;
	
	virtual void BeginPlay() override;

public:

	AARPGPlayerController();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	
	virtual void OnLookVertical(float Scale);
	virtual void OnLookHorizontal(float Scale);

	virtual void OnMoveVertical(float Scale);
	virtual void OnMoveHorizontal(float Scale);

	virtual void OnJump();
	virtual void OnAttack();
	virtual void OnHeavyAttack();
	virtual void OnDodgeFront();
	virtual void OnDodgeBack();
	virtual void OnPlayerUseSkill();

	UFUNCTION(BlueprintCallable)
	virtual void PlayerDied();

	UFUNCTION(BlueprintCallable)
	virtual void OwnedPlayerNoHealth();

	UFUNCTION(BlueprintCallable)
	void SetReadyToAttack(bool InReadyToAttack);

	UFUNCTION(BlueprintCallable)
	void BroadCastPlayerDead();

	UFUNCTION(BlueprintCallable)
	void GainScore(float Value);

	UFUNCTION(BlueprintCallable)
	void GainExp(float Value);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UAttackDamageScalar* GetAttackScalar() { return ScalarSystem; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCharacterData* GetPlayerData() { return PlayerData; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool PlayerIsAlive() const { return !bPlayerFallDown; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float DodgeCooldownRemain() const { return DodgeCooldownCurrent; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float DodgeCooldownTotal() const { return DodgeCooldownLimit; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float SkillCooldownTotal() const { return SkillCoolDownLimit; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float SkillCooldownRemain() const { return SkillCoolDownCurrent; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentScore() const { return Score; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetExpNeed() const { return PlayerData->NeedUpgradeExp; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetExp() const { return PlayerData->CurrentExp; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetPlayerLevel() const { return PlayerData->Level; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetPlayerLifeRemain() const { return LifeRemain; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsReadyToAttack() const { return bReadyToAttack; }
	
	FOnPlayerDiedEvent& GetPlayerDiedEvent() { return OnPlayerDiedEvent; }
};
