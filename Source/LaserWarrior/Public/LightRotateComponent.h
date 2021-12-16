// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DirectionalLight.h"
#include "LightRotateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API ULightRotateComponent : public UActorComponent
{
	GENERATED_BODY()
	ADirectionalLight* OwnerLight;

public:	
	// Sets default values for this component's properties
	ULightRotateComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
