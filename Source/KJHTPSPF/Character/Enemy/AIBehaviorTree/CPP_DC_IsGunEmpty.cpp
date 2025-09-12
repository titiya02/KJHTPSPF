// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DC_IsGunEmpty.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/CPP_AICharacter.h"
#include "Controller/CPP_AIController.h"
#include "Item/Weapon/CPP_Basegun.h"
#include "KJHTPSPF.h"

bool UCPP_DC_IsGunEmpty::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (auto AI = Cast<ACPP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn()))
		if (auto AIGun = Cast<ACPP_Basegun>(AI->GetWeapon(AI->GetWeaponType())))
			if(AIGun->GetCurrentBullet() == 0)
				return true;
	return false;
}
