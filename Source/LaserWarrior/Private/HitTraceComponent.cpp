// Fill out your copyright notice in the Description page of Project Settings.


#include "HitTraceComponent.h"

// Sets default values for this component's properties
UHitTraceComponent::UHitTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bTraceOn = false;
	WeaponMesh = nullptr;

	// ...
}


// Called when the game starts
void UHitTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHitTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(bTraceOn && WeaponMesh.IsValid()) {
		this->Trace();
	}
	// ...
}

void UHitTraceComponent::InitWeapon(UMeshComponent* InWeaponMesh) {
	if(IsValid(InWeaponMesh)) {
		WeaponMesh = InWeaponMesh;
	}
}

void UHitTraceComponent::EnableTrace() {
	bTraceOn = true;
	DamagedActor.Empty();
	DamagedActor.Push(GetOwner());
}

void UHitTraceComponent::DisableTrace() {
	bTraceOn = false;
}

void UHitTraceComponent::Trace() {
	
}

