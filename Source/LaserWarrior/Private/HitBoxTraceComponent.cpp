// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBoxTraceComponent.h"

#include "Attacker.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LaserWarrior/Hitable.h"

UHitBoxTraceComponent::UHitBoxTraceComponent() {

	BoxCenterName = TEXT("BoxCenter");
}

void UHitBoxTraceComponent::InitWeapon(UMeshComponent* InWeaponMesh) {
	Super::InitWeapon(InWeaponMesh);
}

void UHitBoxTraceComponent::EnableTrace() {
	Super::EnableTrace();
	if(WeaponMesh.IsValid()) {
		CenterPos = WeaponMesh->GetSocketLocation(BoxCenterName);
	}
}

void UHitBoxTraceComponent::Trace() {
	Super::Trace();
	TArray<FHitResult> HitResult;
	FVector NewPosition = WeaponMesh->GetSocketLocation(BoxCenterName);
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(),
		CenterPos, NewPosition, BoxHalfSize,
		WeaponMesh->GetComponentRotation(),
		TraceType.GetValue(),
		false,
		DamagedActor,
		EDrawDebugTrace::None,
		HitResult,
		true
		);
	for(auto& Hit : HitResult) {
		auto HitedActor = Hit.Actor;
		if(DamagedActor.Contains(Hit.Actor.Get())) {
			continue;
		} else {
			DamagedActor.Add(Hit.Actor.Get());
		}
		
		if(GetOwner()->Implements<UAttacker>()) {
			Cast<IAttacker>(GetOwner())->Execute_DealAttackDamage(GetOuter(), Hit.GetActor(), Hit);
		}
		
	}
	CenterPos = NewPosition;
}
