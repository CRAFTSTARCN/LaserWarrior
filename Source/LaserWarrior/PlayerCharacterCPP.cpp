// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterCPP.h"
#include "ARPGPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacterCPP::APlayerCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	FollowedCamera= CreateDefaultSubobject<UCameraComponent>(TEXT("Main Cemera"));
	FollowedCamera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowedCamera->bUsePawnControlRotation = false;

	PlayerWeapon = CreateDefaultSubobject<UWeapon>(TEXT("Player Weapon"));
	PlayerWeapon->SetupAttachment(GetMesh());

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(PlayerWeapon);
	WeaponMesh->SetCollisionProfileName("NoCollision");
	
	this->bUseControllerRotationYaw = false;

	RandomStream.Initialize("Ag2S");

	CurrentCombo = 0;
	LastTimeHealthPercentage = 1;
	SelfController = nullptr;

	bEndure = false;
	bInvincible = false;
}

// Called when the game starts or when spawned
void APlayerCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(PlayerData) {
		float NowPercentage = Health / PlayerData->HealthLimit;
		if(LastTimeHealthPercentage >= 0.5f && NowPercentage < 0.5f) {
			ChangeHeartMaterial(NowPercentage);
		} else if(LastTimeHealthPercentage < 0.5f && NowPercentage >= 0.5f) {
			ChangeHeartMaterial(NowPercentage);
		}
		LastTimeHealthPercentage = NowPercentage;
	}
}

// Called to bind functionality to input
void APlayerCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacterCPP::PlayerAttack() {
	if(SelfController) {
		SelfController->GetAttackScalar()->SetCurrentScale(CurrentCombo);
	}
	AttackAnimPlay(CurrentCombo);
	++CurrentCombo;
	CurrentCombo %= 4;
}

void APlayerCharacterCPP::PlayerHeavyAttack() {
	CurrentCombo = 0;
	if(SelfController) {
		SelfController->GetAttackScalar()->SetCurrentScale(4);
	}
	HeavyAttackAnimPlay();
}

void APlayerCharacterCPP::PlayerUseSkill(float ManaCost) {
	Mana -= ManaCost;
	SkillAnimePlay();
}

void APlayerCharacterCPP::ResetAttackCombo(int32 InAttackCombo) {
	if(InAttackCombo > 3) {
		InAttackCombo = 0;
	}
	CurrentCombo = InAttackCombo;
}

void APlayerCharacterCPP::SetUpPlayerData(UCharacterData* InPlayerData) {
	
	if(IsValid(InPlayerData)) {
		PlayerData = InPlayerData;
		Health = InPlayerData->HealthLimit;
		Mana = InPlayerData->ManaLimit;

		FString Message = FString::Printf(TEXT("Health %f, Mana %f"), Health, Mana);
		UKismetSystemLibrary::PrintString(this,Message);
	}
	
}

void APlayerCharacterCPP::SetPlayerMana(float InMama) {
	Mana = InMama;
}

void APlayerCharacterCPP::SetPlayerHealth(float InHealth) {
	Health = InHealth;
}

void APlayerCharacterCPP::InitController(AARPGPlayerController* InController) {
	if(InController) {
		SelfController = InController;
	}
}

void APlayerCharacterCPP::ReduceHealth(float Value) {
	if(Value < 0.f) {
		return;
	}
	Health -= Value;
	if(Health <= 0) {
		AARPGPlayerController* ARPGController = Cast<AARPGPlayerController>(GetController());
		if(ARPGController) {
			ARPGController->OwnedPlayerNoHealth();
		}
	}
}

void APlayerCharacterCPP::AddHealthByPercentage(float Percentage) {
	if(SelfController && SelfController->PlayerIsAlive()) {
		float TotalHealth = SelfController->GetPlayerData()->HealthLimit;
		float Addition = Percentage * TotalHealth;
		if(Addition + Health > TotalHealth) {
			Health = TotalHealth;
		} else {
			Health += Addition;
		}
	}
}

void APlayerCharacterCPP::AddManaByPercentage(float Percentage) {
	if(SelfController && SelfController->PlayerIsAlive()) {
		float TotalMana = SelfController->GetPlayerData()->ManaLimit;
		float Addition = Percentage * TotalMana;
		if(Addition + Mana > TotalMana) {
			Mana = TotalMana;
		} else {
			Mana += Addition;
		}
	}
}

float APlayerCharacterCPP::CalculateSkillDamage() {
	float Damage = PlayerData->Atk;
	Damage += PlayerWeapon->GetAttack();

	float Desition = RandomStream.FRandRange(0.0,100.0);
	
	if(Desition < PlayerData->CriticalRate) {
		Damage += (PlayerData->CriticalDamage / 100 * Damage);
	}

	if(SelfController) {
		Damage *= SelfController->GetAttackScalar()->GetScaleById(5);
	}
	
	return Damage;
}


void APlayerCharacterCPP::Destroyed() {
	Super::Destroyed();
}

float APlayerCharacterCPP::DealAttackDamage_Implementation(AActor* Hitted, const FHitResult& HitResult) {
	if(SelfController && SelfController->PlayerIsAlive()) {
		float Damage = PlayerData->Atk;
		Damage += PlayerWeapon->GetAttack();

		float Desition = RandomStream.FRandRange(0.0,100.0);
	
		if(Desition < PlayerData->CriticalRate) {
			Damage += (PlayerData->CriticalDamage / 100 * Damage);
		}

		if(SelfController) {
			Damage *= SelfController->GetAttackScalar()->GetCurrentScale();
		}

		IHitable* HittedHitable = Cast<IHitable>(Hitted);
		if(HittedHitable) {
			HittedHitable->Execute_GetHit(Hitted, this, HitResult, Damage);
		}
	
		return Damage;
	}
	return 0.0f;
}

float APlayerCharacterCPP::GetHit_Implementation(AActor* Hitter, const FHitResult& Hit, float AtkDamage) {
	if(Health > 0 && !bInvincible) {
		float SufferDamage = AtkDamage - PlayerData->Defence;
		ReduceHealth(SufferDamage);
		if(Health > 0 && !bEndure) {
			HittedAnimePlay();
		}
		return SufferDamage;
	}
	return 0;
}

void APlayerCharacterCPP::PlayerFall_Implementation() {
	
}

