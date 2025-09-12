// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "F_ItemInfo.generated.h"

USTRUCT(BlueprintType)
struct F_ItemInfo
{
	GENERATED_BODY()

public:
	F_ItemInfo() : ItemName(TEXT("None")), ItemCounts(-1)
	{}

	UPROPERTY(EditDefaultsOnly)
	FString ItemName;

	UPROPERTY(EditDefaultsOnly)
	int ItemCounts;
};
