// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_UserGaugeBar.h"
#include "KJHTPSPF.h"
#include "Components/ProgressBar.h"

void UCPP_UserGaugeBar::UpdateGaugeBar(double PercentValue)
{
	GaugeBar->SetPercent(PercentValue);
}
