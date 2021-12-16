// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorComponent.h"

// Sets default values for this component's properties
UElevatorComponent::UElevatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	RunStatus = false;
	LastRunStat = false;
	MovementComponent = nullptr;
	// ...
}


// Called when the game starts
void UElevatorComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UElevatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float ActorHeight = GetOwner()->GetActorLocation().Z;
	if(RunStatus && !LastRunStat) {
		OriHeight = ActorHeight;
		if(MovementComponent) {
			float Speed = MovementComponent->GetMaxSpeed();
			MovementComponent->SetVelocityInLocalSpace(FVector(0,0,Speed));
		}
	} else if(!RunStatus && LastRunStat) {
		float Speed = MovementComponent->GetMaxSpeed();
		MovementComponent->SetVelocityInLocalSpace(FVector(0,0,-Speed));
	}

	if(RunStatus) {
		if(ActorHeight >= OriHeight + TargetHeight && MovementComponent) {
			MovementComponent->SetVelocityInLocalSpace(FVector(0,0,0));
		}
	}

	if(!RunStatus) {
		if(ActorHeight <= OriHeight && MovementComponent) {
			MovementComponent->SetVelocityInLocalSpace(FVector(0,0,0));
		}
	}

	LastRunStat = RunStatus;
	// ...
}

void UElevatorComponent::SetMovementComponent(UProjectileMovementComponent* InMovement) {
	if(IsValid(InMovement)) {
		MovementComponent = InMovement;
	}
}