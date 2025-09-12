// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(TestKJH, Log, All)

#define AssignDefaultSubobject(Variable)\
(Variable = CreateDefaultSubobject<std::remove_reference<decltype(*Variable)>::type>(#Variable))

#define SpawnActorAssign(Actor, Location, Rotator, Parameter)\
GetWorld()->SpawnActor<std::remove_reference<decltype(*Actor)>::type>(Location, Rotator, Patameter)

#define PlayAnimMontageData(MontageData)\
PlayAnimMontage(##MontageData.Montage, ##MontageData.PlayRate,## MontageData.Section)

#define EnumToFName(enumValue)\
(StaticEnum<decltype(enumValue)>()->GetNameByValue(static_cast<int64>(enumValue)))