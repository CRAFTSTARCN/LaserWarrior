// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCPP.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ABulletCPP::ABulletCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Default Root"));
	SetRootComponent(DefaultRoot);
	
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Movement"));
	LifeTime = 7;
	Live = 0;
}

// Called when the game starts or when spawned
void ABulletCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Live += DeltaTime;
	if(Live >= LifeTime) {
		Destroy();
	}

}

void ABulletCPP::SetShooter(AEnemy* InShooter) {
	if(IsValid(InShooter)) {
		Shooter = InShooter;
	}
}

void ABulletCPP::HitCharacter(APlayerCharacterCPP* HittedPlayer, const FHitResult& HitResult) {
	if(IsValid(Shooter)) {
		Shooter->Execute_DealAttackDamage(Shooter, HittedPlayer, HitResult);
	}
}

