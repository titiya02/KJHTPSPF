// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WeaponAttach.h"
#include "Character/CPP_Character.h"

void UCPP_WeaponAttach::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Anim)
{
	if (AActor* Owner = Mesh->GetOwner())
	{
		if (ACPP_Character* Character = Cast<ACPP_Character>(Owner))
		{
				Character->EquipWeapon();
		}
	}
}
