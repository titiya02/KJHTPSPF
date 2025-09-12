// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enum/ECharacterWeapon.h"
#include "CPP_CharacterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class E4WayDirection : uint8
{
	Front,
	Back,
	Right,
	Left
};

UENUM(BlueprintType)
enum class RootYawOffsetMode : uint8
{
	Accumulate,
	BlendOut,
	Hold
};

UCLASS()
class KJHTPSPF_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe))
	void UpdateCharacterDirection();

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetRootYawOffset(double Value);

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double Direction = 0;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	RootYawOffsetMode RootYawOffsetMode = RootYawOffsetMode::Accumulate;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	E4WayDirection CharacterDirection = E4WayDirection::Front;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterWeapon CharacterWeapon = ECharacterWeapon::Unknown;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsRun = false;

	double MinClampAngle = -120;
	double MaxClampAngle = 120;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double RootYawOffset = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double AimYaw = 0;
};
 