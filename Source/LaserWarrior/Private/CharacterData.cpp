// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterData.h"

float UCharacterData::CalGap(float Data, float DataTop) {
	return (DataTop - Data) / (float)(LevelLimit - Level);
}

// Sets default values for this component's properties
UCharacterData::UCharacterData()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	LevelLimit = 90;
	// ...
}


// Called when the game starts
void UCharacterData::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterData::Upgrade() {
	if(Level < LevelLimit) {
		HealthLimit += CalGap(HealthLimit, HealthLimitTop);
		ManaLimit += CalGap(ManaLimit, ManaLimitTop);
		Atk += CalGap(Atk, AtkTop);
		Defence += CalGap(Defence,DefenceTop);
		CriticalRate += CalGap(CriticalRate, 25.f);
		CriticalDamage += CalGap(CriticalDamage, 100.f);
		NeedUpgradeExp *= ExpIncreaseRate;
	}
	Level += 1;
}

