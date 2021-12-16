// Fill out your copyright notice in the Description page of Project Settings.


#include "HitLineTraceComponent.h"
#include "Attacker.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LaserWarrior/Hitable.h"

void UHitLineTraceComponent::InitWeapon(UMeshComponent* InWeaponMesh) {
	Super::InitWeapon(InWeaponMesh);
	if(WeaponMesh.IsValid()) {
		SocketName = WeaponMesh->GetAllSocketNames();
	}
}

void UHitLineTraceComponent::Trace() {
	Super::Trace();
	for (auto& Name : SocketName) {
		FVector NewPosition = WeaponMesh->GetSocketLocation(Name);
		FVector* BeginPos = SocketPosition.Find(Name);
		if(!BeginPos) continue;
		TArray<FHitResult> Hits;
		UKismetSystemLibrary::LineTraceMulti(
			GetWorld(),
			*BeginPos,
			NewPosition,
			TraceType.GetValue(),
			false,
			DamagedActor,
			EDrawDebugTrace::None,
			Hits,
			true
			);
		for(auto& Hit : Hits) {
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
		*BeginPos = NewPosition;
	}
}

void UHitLineTraceComponent::EnableTrace() {
	Super::EnableTrace();

	for (auto& Name : SocketName) {
		if(WeaponMesh.IsValid()) {
			SocketPosition.Add(Name,WeaponMesh->GetSocketLocation(Name));
		}
	}
}
