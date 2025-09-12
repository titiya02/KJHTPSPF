// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CharacterAnimInstance.h"
#include "KJHTPSPF.h"
#include "CPP_Player.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (auto* OwningCharacter = Cast<ACPP_Character>(GetOwningActor()))
		CharacterWeapon = OwningCharacter->GetWeaponType();
	if(auto* OwningPlayer = Cast<ACPP_Player>(GetOwningActor()))
		bIsRun = OwningPlayer->GetRunning();
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UCharacterAnimInstance::UpdateCharacterDirection()
{
	if (abs(Direction) <= 60.0)
		CharacterDirection = E4WayDirection::Front;
	else if (abs(Direction) >= 120.0)
		CharacterDirection = E4WayDirection::Back;
	else if (Direction > 0)
		CharacterDirection = E4WayDirection::Right;
	else
		CharacterDirection = E4WayDirection::Left;
}

void UCharacterAnimInstance::SetRootYawOffset(double Value)
{
	RootYawOffset =  UKismetMathLibrary::ClampAngle(UKismetMathLibrary::NormalizeAxis(Value), MinClampAngle, MaxClampAngle);
	AimYaw = -RootYawOffset;
}
