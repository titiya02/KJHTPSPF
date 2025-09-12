// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MontageDataAsset.h"

FMontageData UCPP_MontageDataAsset::GetMontageData(int index)
{
	if (MontageData.IsValidIndex(index))
		return MontageData[index];
	return FMontageData();
}
