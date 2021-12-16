// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackDamageScalar.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UAttackDamageScalar : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackDamageScalar();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, float> ScaleTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentScale;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentScale() const { return CurrentScale; }

	UFUNCTION(BlueprintCallable)
	void SetCurrentScale(int32 Id);

	UFUNCTION(BlueprintCallable)
	float GetScaleById(int32 Id);
		
};
