// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ChangeWeapon.h"
#include "Character/CPP_Player.h"

void UCPP_ChangeWeapon::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Anim)
{
	if (AActor* Owner = Mesh->GetOwner())
	{
		if (ACPP_Player* Player = Cast<ACPP_Player>(Owner))
		{
			Player->SetStateIdle();
			Player->ChangeWeapon();
		}
	}
}
