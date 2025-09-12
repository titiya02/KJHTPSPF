// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CPP_Item.h"
#include "Enum/ECharacterWeapon.h"
#include "CPP_BaseWeapon.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_BaseWeapon : public ACPP_Item
{
	GENERATED_BODY()

public:
	ACPP_BaseWeapon();

	ECharacterWeapon GetWeaponType();
	FName GetSocketOnArmed();
	FName GetSocketOnUnarmed();

	void BeginActionBStarted() override;
	void BeginActionBCompleted() override;

	virtual void UpdateWeaponUI();
protected:
	virtual void BeginPlay() override;
	
	virtual void BeginActionAStarted() override;
	virtual void BeginActionACompleted() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly)
	ECharacterWeapon WeaponType = ECharacterWeapon::Unknown;

	UPROPERTY(EditDefaultsOnly)
	double Damage = 0;
	
	UPROPERTY(EditDefaultsOnly)
	FName SocketOnArmed;

	UPROPERTY(EditDefaultsOnly)
	FName SocketOnUnarmed;


};
