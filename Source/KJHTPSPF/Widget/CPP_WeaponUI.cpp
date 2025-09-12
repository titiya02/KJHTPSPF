// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WeaponUI.h"
#include "Components/TextBlock.h"

void UCPP_WeaponUI::UpdateAmmo(FString Text)
{
	CurrentAmmo->SetText(FText::FromString(Text));
}

void UCPP_WeaponUI::UpdateWeaponName(FString Text)
{
	WeaponName->SetText(FText::FromString(Text));
}
