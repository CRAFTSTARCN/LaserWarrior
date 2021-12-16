// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitTraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UHitTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitTraceComponent();

protected:
	// Called when the game starts
	TWeakObjectPtr<UMeshComponent> WeaponMesh;
	TArray<AActor*> DamagedActor;
	bool bTraceOn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> TraceType;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void InitWeapon(UMeshComponent* InWeaponMesh);

	UFUNCTION(BlueprintCallable)
	virtual void EnableTrace();

	UFUNCTION(BlueprintCallable)
	virtual void DisableTrace();

	UFUNCTION(BlueprintCallable)
	virtual void Trace();
};
