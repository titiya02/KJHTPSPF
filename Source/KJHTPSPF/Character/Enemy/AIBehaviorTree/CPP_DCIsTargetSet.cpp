// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DCIsTargetSet.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KJHTPSPF.h"

bool UCPP_DCIsTargetSet::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	UBlackboardComponent* OwnerBlackboard = OwnerComp.GetBlackboardComponent();

	if (OwnerBlackboard->GetValueAsObject(BlackboardKey.SelectedKeyName) != nullptr)
		return true;
	return false;
}
