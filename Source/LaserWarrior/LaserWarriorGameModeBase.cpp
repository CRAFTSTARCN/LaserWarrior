// Copyright Epic Games, Inc. All Rights Reserved.


#include "LaserWarriorGameModeBase.h"

#include "ARPGPlayerController.h"


ALaserWarriorGameModeBase::ALaserWarriorGameModeBase() {
	PlayerControllerClass = AARPGPlayerController::StaticClass();
}

void ALaserWarriorGameModeBase::RestartPlayer(AController* NewPlayer) {
	Super::RestartPlayer(NewPlayer);
}


