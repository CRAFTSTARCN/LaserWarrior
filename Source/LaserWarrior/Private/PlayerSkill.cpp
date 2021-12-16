// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill.h"

// Sets default values
APlayerSkill::APlayerSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
	this->SetRootComponent(DamageBox);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Compnent"));
	
	LifeTime = 4;
	TimeCounter = 0;
	CarryDamage = 0;
	
}

// Called when the game starts or when spawned
void APlayerSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeCounter += DeltaTime;

	if(TimeCounter > LifeTime) {
		Destroy();
	}

}

void APlayerSkill::OnHitEnemy(AEnemy* HittedEnemy, const FHitResult& Hit) {
	if(IsValid(HittedEnemy)) {
		HittedEnemy->Execute_GetHit(HittedEnemy, GetWorld()->GetFirstPlayerController()->GetPawn(), Hit, CarryDamage);
	}
}

