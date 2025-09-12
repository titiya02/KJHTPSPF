// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseWeapon.h"
#include "KJHTPSPF.h"
#include "Controller/CPP_PlayerController.h"

ACPP_BaseWeapon::ACPP_BaseWeapon()
{
	SetRootComponent(AssignDefaultSubobject(SkeletalMesh));
	ItemCollision->SetupAttachment(SkeletalMesh);
	ItemType = EItemType::Weapon;
}

ECharacterWeapon ACPP_BaseWeapon::GetWeaponType()
{
	return WeaponType;
}

FName ACPP_BaseWeapon::GetSocketOnArmed()
{
	return SocketOnArmed;
}

FName ACPP_BaseWeapon::GetSocketOnUnarmed()
{
	return SocketOnUnarmed;
}

void ACPP_BaseWeapon::BeginActionBStarted()
{
	Super::BeginActionBStarted();
}

void ACPP_BaseWeapon::BeginActionBCompleted()
{
	Super::BeginActionBCompleted();
}

void ACPP_BaseWeapon::UpdateWeaponUI()
{
	if (auto PlayerController = Cast<ACPP_PlayerController>(GetInstigatorController()))
	{
		FString Name = StaticEnum<ECharacterWeapon>()->GetNameStringByValue((int64)WeaponType);
		PlayerController->GetCanvas()->UpdateWeaponUI(0, 0, Name);
	}
}

void ACPP_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_BaseWeapon::BeginActionAStarted()
{
	Super::BeginActionAStarted();	
}

void ACPP_BaseWeapon::BeginActionACompleted()
{
	Super::BeginActionACompleted();
}

