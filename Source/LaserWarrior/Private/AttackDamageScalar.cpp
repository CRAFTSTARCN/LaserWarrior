// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackDamageScalar.h"

// Sets default values for this component's properties
UAttackDamageScalar::UAttackDamageScalar()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackDamageScalar::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackDamageScalar::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackDamageScalar::SetCurrentScale(int32 Id) {
	CurrentScale = GetScaleById(Id);
}

float UAttackDamageScalar::GetScaleById(int32 Id) {
	float* Scale = ScaleTable.Find(Id);
	if(Scale == nullptr) {
		return 0; 
	}
	return *Scale;
}

