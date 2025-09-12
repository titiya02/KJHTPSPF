#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Arming,
	Reloading,
	Acting,
	Damaged,
	Died
};
