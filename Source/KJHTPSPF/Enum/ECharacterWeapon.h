#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterWeapon : uint8
{
	Unknown,
	Machinegun,
	Shotgun,
	Melee,
	Grenade
};