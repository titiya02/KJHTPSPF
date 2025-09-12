// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseWeapon.h"
#include "CPP_Grenade.generated.h"

class ACPP_ExplosiveEffect;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Grenade : public ACPP_BaseWeapon
{
	GENERATED_BODY()
	
	ACPP_Grenade();

public:
	void StartedThrow();

protected:
	virtual void Tick(float Deltatime) override;

	void BeginActionAStarted() override;
	void BeginActionACompleted() override;

private:
	void Explosive();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACPP_ExplosiveEffect> EffectClass;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* Projectile;

	UPROPERTY(EditDefaultsOnly)
	bool bIsFlash = false;

	bool bIsCharged = false;
	
	double ExplosiveRadius = 700;

	double testTime = 0;
};
