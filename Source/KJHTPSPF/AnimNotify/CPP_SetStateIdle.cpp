// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SetStateIdle.h"
#include "Character/CPP_Player.h"

void UCPP_SetStateIdle::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Anim)
{
	if (AActor* Owner = Mesh->GetOwner())
	{
		if (ACPP_Character* Character = Cast<ACPP_Character>(Owner))
		{
			Character->SetStateIdle();
		}
	}
}
