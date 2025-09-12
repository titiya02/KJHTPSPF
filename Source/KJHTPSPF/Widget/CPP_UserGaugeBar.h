// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserGaugeBar.generated.h"

class UProgressBar;

UCLASS(Abstract)
class KJHTPSPF_API UCPP_UserGaugeBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateGaugeBar(double PercentValue);

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* GaugeBar;
};
