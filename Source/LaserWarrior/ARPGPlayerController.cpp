// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGPlayerController.h"
#include "PlayerCharacterCPP.h"
#include "LaserWarriorGameModeBase.h"
#include "LWGameInstance.h"

void AARPGPlayerController::DecreaceCoolDown(float& CoolDown, float Delta) {
	if(CoolDown > 0) {
		CoolDown -= Delta;
		if(CoolDown < 0) {
			CoolDown = 0;
		}
	}
}

void AARPGPlayerController::BeginPlay() {
	Super::BeginPlay();
	OnPlayerDiedEvent.AddDynamic(this,&AARPGPlayerController::PlayerDied);
}

AARPGPlayerController::AARPGPlayerController() {
	PlayerData = CreateDefaultSubobject<UCharacterData>(TEXT("Player Data"));
	ScalarSystem = CreateDefaultSubobject<UAttackDamageScalar>(TEXT("Scalar System"));
	
	PlayerCharacter = nullptr;
	
	DodgeCooldownCurrent = 0;
	DodgeCooldownLimit = 0;
	SkillCoolDownCurrent = 0;
	SkillCoolDownLimit = 0;

	SkillManaRequire = 30;
	Score = 0;

	bAllowDodge = true;
}

void AARPGPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	DecreaceCoolDown(DodgeCooldownCurrent, DeltaSeconds);
	DecreaceCoolDown(SkillCoolDownCurrent, DeltaSeconds);
}

void AARPGPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<APlayerCharacterCPP>(InPawn);
	bReadyToAttack = true;
	bPlayerFallDown = false;
	PlayerCharacter->InitController(this);
	PlayerCharacter->SetUpPlayerData(PlayerData);
}

void AARPGPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAxis("LookUp", this, &AARPGPlayerController::OnLookVertical);
	InputComponent->BindAxis("LookAround", this, &AARPGPlayerController::OnLookHorizontal);

	InputComponent->BindAxis("MoveForward", this, &AARPGPlayerController::OnMoveVertical);
	InputComponent->BindAxis("MoveRight", this, &AARPGPlayerController::OnMoveHorizontal);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AARPGPlayerController::OnJump);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AARPGPlayerController::OnAttack);
	InputComponent->BindAction("HeavyAttack", IE_Pressed, this, &AARPGPlayerController::OnHeavyAttack);

	InputComponent->BindAction("DodgeFront", IE_Pressed, this, &AARPGPlayerController::OnDodgeFront);
	InputComponent->BindAction("DodgeBack", IE_Pressed, this, &AARPGPlayerController::OnDodgeBack);

	InputComponent->BindAction("UseSkill", IE_Pressed, this, &AARPGPlayerController::OnPlayerUseSkill);
}


void AARPGPlayerController::OnLookVertical(float Scale) {
	AddPitchInput(Scale);
}

void AARPGPlayerController::OnLookHorizontal(float Scale) {
	AddYawInput(Scale);
}

void AARPGPlayerController::OnMoveVertical(float Scale) {
	if(PlayerCharacter && Scale != 0.f && !bPlayerFallDown) {
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		PlayerCharacter->AddMovementInput(Direction, Scale);
	}
}

void AARPGPlayerController::OnMoveHorizontal(float Scale) {
	if(PlayerCharacter && Scale != 0.f && !bPlayerFallDown) {
		const FRotator Rotation =GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		PlayerCharacter->AddMovementInput(Direction, Scale);
	}
}

void AARPGPlayerController::OnJump() {
	if(PlayerCharacter && !bPlayerFallDown) {
		PlayerCharacter->Jump();
	}
}

void AARPGPlayerController::OnAttack() {
	if(PlayerCharacter && bReadyToAttack && !bPlayerFallDown) {
		PlayerCharacter->PlayerAttack();
	}
}

void AARPGPlayerController::OnHeavyAttack() {
	if(PlayerCharacter && bReadyToAttack && !bPlayerFallDown) {
		PlayerCharacter->PlayerHeavyAttack();
	}
}

void AARPGPlayerController::OnDodgeFront() {
	if(PlayerCharacter && DodgeCooldownCurrent <= 0.f && !bPlayerFallDown && bAllowDodge) {
		DodgeCooldownCurrent = DodgeCooldownLimit;
		PlayerCharacter->PlayDodgeForward();
	}
}

void AARPGPlayerController::OnDodgeBack() {
	if(PlayerCharacter && DodgeCooldownCurrent <= 0.f && !bPlayerFallDown && bAllowDodge) {
		DodgeCooldownCurrent = DodgeCooldownLimit;
		PlayerCharacter->PlayDodgeBackward();
	}
}

void AARPGPlayerController::OnPlayerUseSkill() {
	if(PlayerCharacter && bReadyToAttack && !bPlayerFallDown && SkillCoolDownCurrent <= 0.f && PlayerCharacter->GetMana() > SkillManaRequire) {
		SkillCoolDownCurrent = SkillCoolDownLimit;
		PlayerCharacter->PlayerUseSkill(SkillManaRequire);
	}
}

void AARPGPlayerController::PlayerDied() {
	PlayerCharacter->Destroy();
	PlayerCharacter = nullptr;
	if(--LifeRemain) {
		if(UWorld* World = GetWorld()) {
			if(ALaserWarriorGameModeBase* GameMode = Cast<ALaserWarriorGameModeBase>(World->GetAuthGameMode())) {
				GameMode->RestartPlayer(this);
			}
		}
	} else {
		ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
		if(Game) {
			Game->GameOver(Score);
		}
	}
}

void AARPGPlayerController::OwnedPlayerNoHealth() {
	bReadyToAttack = false;
	bPlayerFallDown = true;
	if(PlayerCharacter) {
		PlayerCharacter->PlayerFall();
	}
}

void AARPGPlayerController::SetReadyToAttack(bool InReadyToAttack) {
	bReadyToAttack = InReadyToAttack;
}

void AARPGPlayerController::BroadCastPlayerDead() {
	OnPlayerDiedEvent.Broadcast();
}

void AARPGPlayerController::GainScore(float Value) {
	Score += Value;
}

void AARPGPlayerController::GainExp(float Value) {
	PlayerData->CurrentExp += Value;
	if(PlayerData->CurrentExp >= PlayerData->NeedUpgradeExp && PlayerData->Level < PlayerData->LevelLimit) {
		PlayerData->CurrentExp -= PlayerData->NeedUpgradeExp;
		PlayerData->Upgrade();
		if(!bPlayerFallDown) {
			PlayerCharacter->SetUpPlayerData(PlayerData);
		}
	}
}





