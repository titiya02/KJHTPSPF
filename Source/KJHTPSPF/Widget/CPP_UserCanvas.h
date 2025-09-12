// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserCanvas.generated.h"

class UCanvasPanel;
class UCPP_UserGaugeBar;
class UCPP_CrossHair;
class UCPP_WeaponUI;

UCLASS(Abstract)
class KJHTPSPF_API UCPP_UserCanvas : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateBossHealthBar(double PercentValue);
	void UpdateBossHealthBarVisibility(bool Value = false);

	void UpdateHealthBar(double PercentValue);

	void UpdateCrossHairVisible(bool bIsVisible = false);

	void UpdateWeaponUI(int CurrentAmmo = 0, int MaxAmmo = 0, FString WeaponName = TEXT(""));
protected:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* PlayCanvas;

	UPROPERTY(meta = (BindWidget))
	UCPP_UserGaugeBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UCPP_UserGaugeBar* BossHealthBar;

	UPROPERTY(meta = (BindWidget))
	UCPP_CrossHair* CrossHair;

	UPROPERTY(meta = (BindWidget))
	UCPP_WeaponUI* WeaponUI;
};
