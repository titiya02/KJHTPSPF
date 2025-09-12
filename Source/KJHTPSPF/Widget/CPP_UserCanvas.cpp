// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_UserCanvas.h"
#include "KJHTPSPF.h"
#include "Components/CanvasPanel.h"
#include "CPP_UserGaugeBar.h"
#include "CPP_CrossHair.h"
#include "CPP_WeaponUI.h"

void UCPP_UserCanvas::UpdateBossHealthBar(double PercentValue)
{
	BossHealthBar->UpdateGaugeBar(PercentValue);
}

void UCPP_UserCanvas::UpdateBossHealthBarVisibility(bool Value)
{
	if (Value)
		BossHealthBar->SetVisibility(ESlateVisibility::Visible);
	else
		BossHealthBar->SetVisibility(ESlateVisibility::Hidden);
}

void UCPP_UserCanvas::UpdateHealthBar(double PercentValue)
{
	HealthBar->UpdateGaugeBar(PercentValue);
}

void UCPP_UserCanvas::UpdateCrossHairVisible(bool bIsVisible)
{
	if(bIsVisible)
		CrossHair->SetVisibility(ESlateVisibility::Visible);
	else
		CrossHair->SetVisibility(ESlateVisibility::Hidden);
}

void UCPP_UserCanvas::UpdateWeaponUI(int CurrentAmmo, int MaxAmmo, FString WeaponName)
{
	if (WeaponName.IsEmpty())
	{
		WeaponUI->UpdateAmmo(TEXT(""));
		WeaponUI->UpdateWeaponName(TEXT(""));
	}
	else if (MaxAmmo == 0)
	{
		WeaponUI->UpdateAmmo(TEXT(""));
		WeaponUI->UpdateWeaponName(WeaponName);
	}
	else
	{
		FString Ammo = FString::FromInt(CurrentAmmo) + TEXT(" / ") + FString::FromInt(MaxAmmo);
		WeaponUI->UpdateAmmo(Ammo);
		WeaponUI->UpdateWeaponName(WeaponName);		
	}

}
