// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_ReturnPatrol.h"
#include "KJHTPSPF.h"
//#include "Controller/CPP_AIMinionController.h"
#include "Controller/CPP_AIMinionController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/CPP_AICharacter.h"

EBTNodeResult::Type UTK_ReturnPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = Cast<ACPP_AIMinionController>(OwnerComp.GetAIOwner());
	auto Blackboard = OwnerComp.GetBlackboardComponent();

	AIController->BackToPatrol(Blackboard->GetValueAsVector(ReturnLocationKey.SelectedKeyName));
	
	Blackboard->ClearValue(ReturnLocationKey.SelectedKeyName);
	Blackboard->ClearValue(BlackboardKey.SelectedKeyName);

	Cast<ACPP_AICharacter>(AIController->GetPawn())->SetLifeGaugeVisibility(false);
	//UE_LOG(TestKJH, Log, TEXT("%s"), *BlackboardKey.SelectedKeyName.ToString());

	return EBTNodeResult::Succeeded;
}
