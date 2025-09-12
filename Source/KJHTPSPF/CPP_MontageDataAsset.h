// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structure/F_MontageData.h"
#include "CPP_MontageDataAsset.generated.h"

UCLASS()
class KJHTPSPF_API UCPP_MontageDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	FMontageData GetMontageData(int index);

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FMontageData> MontageData;
};
