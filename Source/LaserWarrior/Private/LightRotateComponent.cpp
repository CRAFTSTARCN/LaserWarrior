// Fill out your copyright notice in the Description page of Project Settings.


#include "LightRotateComponent.h"

// Sets default values for this component's properties
ULightRotateComponent::ULightRotateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Speed = 1.0f;
	// ...
}


// Called when the game starts
void ULightRotateComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerLight = Cast<ADirectionalLight>(GetOwner());
	// ...
	
}


// Called every frame
void ULightRotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(OwnerLight) {
		float Rotate = DeltaTime*Speed;
		OwnerLight->AddActorLocalRotation(FRotator(0,Rotate,0));
	}
	// ...
}

