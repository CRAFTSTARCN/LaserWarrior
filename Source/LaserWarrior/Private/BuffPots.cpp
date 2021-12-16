// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffPots.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABuffPots::ABuffPots()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerController = nullptr;

	DefaultRoot = CreateDefaultSubobject<USphereComponent>(TEXT("Default Root"));
	SetRootComponent(DefaultRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DefaultRoot);
	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent-> ProjectileGravityScale = 0;
	
	SlayTime = 0;
	TimeCount = 0;
}

// Called when the game starts or when spawned
void ABuffPots::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void ABuffPots::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(PlayerController && TimeCount > SlayTime) {
		APawn* FollowedCharacter = PlayerController->GetPawn();
		if(FollowedCharacter) {
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),FollowedCharacter->GetActorLocation());
			FVector Direction = FVector::ForwardVector;
			Direction = Rotator.RotateVector(Direction) * MovementComponent->GetMaxSpeed();
			MovementComponent->SetVelocityInLocalSpace(Direction);
		}
	} else {
		TimeCount += DeltaTime;
	}
}

