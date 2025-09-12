// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GainHealth.h"
#include "Character/CPP_Player.h" 

void UCPP_GainHealth::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (auto Player = Cast<ACPP_Player>(MeshComp->GetOwner()))
	{
		Player->GainHealth();
	}
}
