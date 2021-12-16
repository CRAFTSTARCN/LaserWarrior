// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMemory.h"

#include "LaserWarrior/ARPGPlayerController.h"

// Sets default values for this component's properties
UEnemyMemory::UEnemyMemory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PlayerInSight = false;
	PlayerInAbsoluteRange = false;
	PlayerInMemoryRange = false;
	PlayerIsRemembered = false;
	// ...
}


// Called when the game starts
void UEnemyMemory::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
	AARPGPlayerController* PlayerController = Cast<AARPGPlayerController>(GetWorld()->GetFirstPlayerController());
	if(PlayerController) {
		PlayerController->GetPlayerDiedEvent().AddDynamic(this, &UEnemyMemory::ForgetAll);
	}
}


// Called every frame
void UEnemyMemory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyMemory::ForgetAll() {
	PlayerInSight = false;
	PlayerIsRemembered = false;
	PlayerInAbsoluteRange = false;
	PlayerInMemoryRange = false;
}

void UEnemyMemory::PlayerEnterSight() {
	PlayerInSight = true;
	if(PlayerInMemoryRange) {
		PlayerIsRemembered = true;
	}
}

void UEnemyMemory::PlayerOutSight() {
	PlayerInSight = false;
}

void UEnemyMemory::PlayerEnterAbsoluteRange() {
	PlayerInAbsoluteRange = true;
	PlayerIsRemembered = true;
}

void UEnemyMemory::PlayerOutAbsoluteRange() {
	PlayerInAbsoluteRange = false;
}

void UEnemyMemory::PlayerEnterMemoryRange() {
	PlayerInMemoryRange = true;
	if(PlayerInSight || PlayerInAbsoluteRange) {
		PlayerIsRemembered = true;
	}
}

void UEnemyMemory::PlayerOutMemoryRange() {
	PlayerInMemoryRange = false;
	PlayerIsRemembered = false;
}

bool UEnemyMemory::EnemyActivated() const {
	return PlayerIsRemembered || PlayerInSight || PlayerInAbsoluteRange;
}
