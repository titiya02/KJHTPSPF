// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EraseActors.h"
#include "KJHTPSPF.h"
#include "Character/CPP_Character.h"
#include "Item/Weapon/CPP_MeleeWeapon.h"

void UCPP_EraseActors::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (auto Character = Cast<ACPP_Character>(MeshComp->GetOwner()))
		if (auto Weapon = Cast<ACPP_MeleeWeapon>(Character->GetWeapon(Character->GetWeaponType())))
			Weapon->ClearOverlappedActors();
}
