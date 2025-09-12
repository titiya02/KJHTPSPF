// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ThrowGrenade.h"
#include "Character/Enemy/CPP_AICharacter.h"

void UCPP_ThrowGrenade::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Anim)
{
	if (auto Character = Cast<ACPP_Character>(Mesh->GetOwner()))
	{
		Character->ThrowGrenade();
	}
}
