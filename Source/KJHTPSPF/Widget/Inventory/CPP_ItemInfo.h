// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structure/F_ItemInfo.h"
#include "CPP_ItemInfo.generated.h"

UCLASS()
class KJHTPSPF_API UCPP_ItemInfo : public UObject
{
	GENERATED_BODY()
	
public:
	void SetInfo(int Num, FString Name = "");
	F_ItemInfo GetInfo() const { return ItemInfo; };

protected:
	UPROPERTY(EditDefaultsOnly)
	F_ItemInfo ItemInfo;
};
