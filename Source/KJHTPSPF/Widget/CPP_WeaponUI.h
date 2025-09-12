// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_WeaponUI.generated.h"

class UTextBlock;

UCLASS(Abstract)
class KJHTPSPF_API UCPP_WeaponUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateAmmo(FString Text);

	void UpdateWeaponName(FString Text);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentAmmo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponName;
};
