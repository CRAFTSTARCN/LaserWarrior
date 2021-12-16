// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthBar.h"

UEnemyHealthBar::UEnemyHealthBar(const FObjectInitializer& ObjectInitializer) :
	UUserWidget(ObjectInitializer)
{
	BandedEnemy = nullptr;
	EnemyLevel = 0;
}

void UEnemyHealthBar::InitEnemy(AEnemy* InEnemy) {
	if(InEnemy) {
		BandedEnemy = InEnemy;
	}
}

float UEnemyHealthBar::UpdateHealthPercentage() {
	if(BandedEnemy) {
		EnemyLevel = BandedEnemy->GetEnemyLevel();
		return BandedEnemy->GetHealth() / BandedEnemy->GetHealthLimit();
	}
	return 0.0;
}
