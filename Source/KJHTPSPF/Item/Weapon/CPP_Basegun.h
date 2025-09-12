// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseWeapon.h"
#include "Enum/EBulletType.h"
#include "Kismet/KismetMathLibrary.h"
#include "CPP_Basegun.generated.h"

class UNiagaraComponent;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Basegun : public ACPP_BaseWeapon
{
	GENERATED_BODY()
public:
	ACPP_Basegun();

	void BeginActionBStarted() override;
	void BeginActionBCompleted() override;

	int NeedBullet();
	int GetCurrentBullet() const;
	int GetMaxBullet() const { return MaxBullet; };
	void SetCurrentBullet(int Value);
	EBulletType GetBulletType() const;
	void PlayWeaponMontage(int Index) const;

	double GetBulletVelocity() const { return BulletVelocity; };

	USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalMesh; };

	double GetDamage() const { return Damage; };

	void UpdateWeaponUI() override;
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	FVector GetProjectileDestination();
	virtual void FireBullet();

	void BeginActionAStarted() override;
	void BeginActionACompleted() override;

	virtual void ApplyRecoil();

protected:
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BPBulletClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> GunMontages;

	UPROPERTY(EditAnywhere)
	EBulletType BulletType = EBulletType::Unknown;

	UPROPERTY(VisibleAnywhere)
	bool bIsAimed = false;

	UPROPERTY(VisibleDefaultsOnly)
	double AttackTraceDistance = 50000;

	UPROPERTY(EditDefaultsOnly)
	double BulletVelocity = 0;

	UPROPERTY(VisibleAnywhere)
	int CurrentBullet = 0;

	UPROPERTY(VisibleAnywhere)
	int MaxBullet = 0;

	UPROPERTY(VisibleInstanceOnly)
	double ActionBDeltaTime = 0;

	FActorSpawnParameters SpawnParameters;

	UPROPERTY(EditDefaultsOnly)
	float RecoilPitch = 0;
	
	UPROPERTY(EditDefaultsOnly)
	float RecoilYaw = 0;
};
