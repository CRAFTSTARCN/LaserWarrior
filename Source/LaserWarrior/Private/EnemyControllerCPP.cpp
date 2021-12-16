// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyControllerCPP.h"

#include "LaserWarrior/ARPGPlayerController.h"
#include "LaserWarrior/PlayerCharacterCPP.h"

AEnemyControllerCPP::AEnemyControllerCPP() {
	
}

void AEnemyControllerCPP::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	ControlledEnemy = Cast<AEnemy>(InPawn);
	bReadyAttack = true;
	bIsAlive = true;
}

float AEnemyControllerCPP::OnAttack() {
	if(ControlledEnemy && bReadyAttack && bIsAlive) {
		return ControlledEnemy->Attack();
	}
	return  0.0;
}

void AEnemyControllerCPP::OnEnemyNoHealth(AActor* CausedBy) {

	if(ControlledEnemy) {
		APlayerCharacterCPP* PlayerCharacter = Cast<APlayerCharacterCPP>(CausedBy);
		if(IsValid(PlayerCharacter)) {
			PlayerCharacter->GetARPGController()->GainScore(ControlledEnemy->GetContentScore());
			PlayerCharacter->GetARPGController()->GainExp(ControlledEnemy->GetContentExp());
		}
		ControlledEnemy->EnemyFallDown();
	}
	bIsAlive = false;
	bReadyAttack = false;
}
