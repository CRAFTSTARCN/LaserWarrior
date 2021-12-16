// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatusUICpp.h"

#include "LaserWarrior/ARPGPlayerController.h"
#include "LaserWarrior/PlayerCharacterCPP.h"

void UPlayerStatusUICpp::SetUpPlayerController(AARPGPlayerController* InController) {
	if(IsValid(InController)) {
		PlayerController = InController;
	}
}

float UPlayerStatusUICpp::SetUpHealthInfo() {
	APlayerCharacterCPP* PlayerCharacter = Cast<APlayerCharacterCPP>(PlayerController->GetPawn());

	if(PlayerController) {
		HealthTop = PlayerController->GetPlayerData()->HealthLimit;
	} else {
		HealthTop = 100;
	}

	if(IsValid(PlayerCharacter)) {
		Health = PlayerCharacter->GetHealth();
	} else {
		Health = 0;
	}

	float Percentage = Health / HealthTop;
	if((LastHeathPercentage < 0.5 && Percentage >= 0.5) || (LastHeathPercentage >= 0.5 && Percentage < 0.5)) {
		ChangeHpColor(Percentage);
	}
	LastHeathPercentage = Percentage;

	return Percentage;
}

float UPlayerStatusUICpp::SetManaInfo() {
	APlayerCharacterCPP* PlayerCharacter = Cast<APlayerCharacterCPP>(PlayerController->GetPawn());
	
	float ManaTop = 100;
	if(PlayerController) {
		ManaTop = PlayerController->GetPlayerData()->ManaLimit;
	}

	float Mana = 0;
	if(IsValid(PlayerCharacter)) {
		Mana = PlayerCharacter->GetMana();
	}

	return Mana / ManaTop;
}

void UPlayerStatusUICpp::SetUpCoolDownInfo() {
	if(PlayerController) {
		
		DodgeCoolDownPercentage = PlayerController->DodgeCooldownRemain() / PlayerController->DodgeCooldownTotal();
		SkillCoolDownPercentage = PlayerController->SkillCooldownRemain() / PlayerController->SkillCooldownTotal();
	}
}

void UPlayerStatusUICpp::SetUpScore() {
	PlayerScore = PlayerController->GetCurrentScore();
}

void UPlayerStatusUICpp::SetupExp() {
	if(PlayerController) {
		ExpPercentage = PlayerController->GetExp() / PlayerController->GetExpNeed();
		PlayerLevel = PlayerController->GetPlayerLevel();
	}
	if(ExpPercentage > 1) {
		ExpPercentage = 1;
	}

	
}

void UPlayerStatusUICpp::SetUpLife() {
	if(PlayerController) {
		PlayerLifeRemain = PlayerController->GetPlayerLifeRemain();
	}
}
