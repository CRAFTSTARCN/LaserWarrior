// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyControllerCPP.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);

	EnemyData = CreateDefaultSubobject<UCharacterData>(TEXT("Enemy Data"));
	EnemyData->LevelLimit = 100;
	SelfController = nullptr;

	TotalAttackStage = 1;
	AttackStage = 0;

	bEndure = false;
	bIsBeingHitted = false;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	SelfController = Cast<AEnemyControllerCPP>(GetController());
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::ReduceHealth(float Value, AActor* CausedBy) {
	if(Value < 0.f) {
		return;
	}
	Health -= Value;
	if(Health <= 0) {
		AEnemyControllerCPP* ControlledBy = Cast<AEnemyControllerCPP>(GetController());
		if(ControlledBy) {
			ControlledBy->OnEnemyNoHealth(CausedBy);
		}
	}
}

void AEnemy::InitWithLevel(int32 InLevel) {
	if(InLevel > 1 && InLevel < EnemyData->LevelLimit) {
		for(;EnemyData->Level < InLevel; ) {
			EnemyData->Upgrade();
			ContainsExp *= ExpIncreaseRate;
			ContainsScore += 10;
		}
	}
}

void AEnemy::SetUpStateInfo() {
	Health = EnemyData->HealthLimit;
	Mana = EnemyData->ManaLimit;
}

void AEnemy::Drop() {
	float Decition = RandomStream.FRandRange(0,100);
	float RateSum = 0;
	FVector SpawnPosition = GetActorLocation();
	for(auto It = DropTable.CreateConstIterator(); It; ++It) {
		RateSum += It.Key();
		if(RateSum >= Decition) {
			GetWorld()->SpawnActor(It.Value(), &SpawnPosition);
			break;
		}
	}
}

float AEnemy::Attack() {
	int32 CurrentStage = AttackStage;
	++AttackStage;
	AttackStage %= TotalAttackStage;
	return PlayAttackAnime(CurrentStage);
}


float AEnemy::DealAttackDamage_Implementation(AActor* Hitted, const FHitResult& HitResult) {
	if(SelfController && SelfController->EnemyIsAlive()) {
		float Damage = EnemyData->Atk;
		float Desition = RandomStream.FRandRange(0.0,100.0);
	
		if(Desition < EnemyData->CriticalRate) {
			Damage += (EnemyData->CriticalDamage / 100 * Damage);
		}
		
		IHitable* HittedHitable = Cast<IHitable>(Hitted);
		if(HittedHitable) {
			HittedHitable->Execute_GetHit(Hitted, this, HitResult, Damage);
		}
		return Damage;
	}
	
	return 0.0;
}

float AEnemy::GetHit_Implementation(AActor* Hitter, const FHitResult& Hit, float AtkDamage) {
	if(Health > 0) {
		IHitable::GetHit_Implementation(Hitter, Hit, AtkDamage);
		float DamageSuffered = AtkDamage - EnemyData->Defence;

		FString HittedLog = FString::Printf(TEXT("ATK: %f DEF: %f Suffer Damage: %f"), AtkDamage, EnemyData->Defence, DamageSuffered);
		UKismetSystemLibrary::PrintString(GetWorld(), HittedLog);
		
		ReduceHealth(DamageSuffered, Hitter);
		if(Health > 0 && !bEndure) {
			PlayHittedAnime();
		}
		return DamageSuffered;
	}
	
	return 0;
}

void AEnemy::EnemyFallDown_Implementation() {
	
}
