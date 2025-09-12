// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DC_IsArmed.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/CPP_AICharacter.h"
#include "KJHTPSPF.h"

bool UCPP_DC_IsArmed::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (WeaponNum == -1)
	{
		UE_LOG(TestKJH, Log, TEXT("Plz Select Weapon!"));
		return false;
	}
	else if (WeaponNum == 0)
	{
		if (auto AI = Cast<ACPP_AICharacter>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName)))
			if (AI->GetWeaponType() != ECharacterWeapon::Unknown)
				return true;
	}
	else
	{
		if (auto AI = Cast<ACPP_AICharacter>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName)))
			if (AI->GetWeaponType() != static_cast<ECharacterWeapon>(WeaponNum) ||
				AI->GetWeaponType() == ECharacterWeapon::Unknown)
				return true;
	}	
	return false;
}
