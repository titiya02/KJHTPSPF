// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseWeapon.h"
#include "CPP_MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class KJHTPSPF_API ACPP_MeleeWeapon : public ACPP_BaseWeapon
{
	GENERATED_BODY()
	ACPP_MeleeWeapon();

public:
	void StartCollisionEnable();
	void StopCollisionEnable();

	void ClearOverlappedActors();

	int GetAttackCount() const { return AttackCount; };
	void SetAtackCount(int Value) { AttackCount = Value; };
protected:
	UFUNCTION()
	void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
private:
	void AddAttackedActor(AActor* OverlappedActor);
			 
protected:
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* MeleeWeaponCapsule;

	UPROPERTY(VisibleAnywhere)
	TSet<AActor*> OverlappedActors;

	int AttackCount = 0;
};
