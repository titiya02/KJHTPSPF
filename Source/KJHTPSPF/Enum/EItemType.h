#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Unknown,
	Weapon,
	MachineGunBullet,
	ShotGunBullet,
	Grenade,
	MedicalKit
};