// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BossLaunchMissle.h"
#include "KJHTPSPF.h"
#include "Character/Enemy/CPP_AIBoss.h"

void UCPP_BossLaunchMissle::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Anim)
{
	if (AActor* Owner = Mesh->GetOwner())
	{
		if (auto Boss = Cast<ACPP_AIBoss>(Owner))
		{
			Boss->ActivateSkill();
		}
	}
}
