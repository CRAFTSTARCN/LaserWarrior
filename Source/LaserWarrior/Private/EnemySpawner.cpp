// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "Kismet/KismetSystemLibrary.h"
#include "LaserWarrior/ARPGPlayerController.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Range Box"));
	RangeBox->SetupAttachment(RootComponent);

	RangeBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	RangeBox->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	RangeBox->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Ignore);
	RangeBox->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);

	EnemyInRangeLimit = 10;
	CurrentEnemyInRange = 0;
	TotalSecond = 0;
	LastSpawnTime = 0;
	MinSpawnGap = 16;
	MaxSpawnGap = 32;
	SpawnGap = 16;
	CurrentEnemySpawnLevel = 1;
	UpgradeTimer = 0;
	EnemyUpgradeGap = 90;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	TargetPlayerController = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TotalSecond += DeltaTime;
	UpgradeTimer += DeltaTime;
	
	if(TargetPlayerController && IsValid(TargetPlayerController->GetPawn())) {
		this->SetActorLocation(TargetPlayerController->GetPawn()->GetActorLocation());
		if(TotalSecond - LastSpawnTime >= SpawnGap) {
			if(CurrentEnemyInRange < EnemyInRangeLimit) {
				SpawnRandomPos();
			}
			LastSpawnTime = TotalSecond;
			SpawnGap = RandomStream.FRandRange(MinSpawnGap, MaxSpawnGap);
			MinSpawnDistance = 1500;
		}
	}

	if(UpgradeTimer >= EnemyUpgradeGap) {
		++CurrentEnemySpawnLevel;
		UpgradeTimer -= EnemyUpgradeGap;
	}
}

void AEnemySpawner::SpawnRandomPos() {
	FVector BoxRange = RangeBox->GetScaledBoxExtent();
	float DistanceX = RandomStream.FRandRange(-BoxRange.X, BoxRange.X);
	float DistanceY = RandomStream.FRandRange(-BoxRange.Y, BoxRange.Y);
	if(abs(DistanceX) < MinSpawnDistance) {
		if(DistanceX >= 0) DistanceX = MinSpawnDistance;
		else DistanceX = -MinSpawnDistance;
	}

	if(abs(DistanceY) < MinSpawnDistance) {
		if(DistanceY >= 0) DistanceY = MinSpawnDistance;
		else DistanceY = -MinSpawnDistance;
	}

	DistanceX = DistanceX + GetActorLocation().X;
	DistanceY = DistanceY + GetActorLocation().Y;
	SpawnAtPosition(DistanceX, DistanceY);
}

bool AEnemySpawner::SpawnAtPosition(float X, float Y) {
	FHitResult HitResult;
	bool Hited = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		FVector(X,Y,10000), FVector(X,Y,-10000),
		TraceTypeQuery5,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResult,
		true
		);
	
	if(Hited) {
		FVector SpawnPosition = HitResult.ImpactPoint;
		SpawnPosition.Z += 90;
		int32 ClassIndex = RandomStream.RandRange(1, EnemySpawnedClass.Num())-1;
		if(ClassIndex < 0) return false;
		
		AActor* ActorSpawned = GetWorld()->SpawnActor(EnemySpawnedClass[ClassIndex].Get(),&SpawnPosition);

		AARPGPlayerController* ARPGController = Cast<AARPGPlayerController>(TargetPlayerController);
		if(ARPGController && ActorSpawned) {
			int32 PlayerLevel = ARPGController->GetPlayerLevel();
			int32 SpawnLevel = CurrentEnemySpawnLevel;
			int LevelGap = (int32)ceilf((float)PlayerLevel * 0.1);
			if(SpawnLevel > PlayerLevel + LevelGap) {
				SpawnLevel = PlayerLevel + LevelGap;
			} else if(SpawnLevel < PlayerLevel - LevelGap) {
				SpawnLevel = PlayerLevel - LevelGap;
			}
			
			AEnemy* EnenmySpawned = Cast<AEnemy>(ActorSpawned);
			EnenmySpawned->InitWithLevel(SpawnLevel);
			EnenmySpawned->SetUpStateInfo();
		}
		return ActorSpawned != nullptr;
	}
	return false;
}

