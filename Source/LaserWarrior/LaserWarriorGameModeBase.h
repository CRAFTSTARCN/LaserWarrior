// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LaserWarriorGameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class LASERWARRIOR_API ALaserWarriorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	
public:
	ALaserWarriorGameModeBase();

	virtual void RestartPlayer(AController* NewPlayer) override;
	
};
