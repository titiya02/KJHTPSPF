// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_MoveBackToPosition.h"
#include "Controller/CPP_AIBossController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTK_MoveBackToPosition::UTK_MoveBackToPosition()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UTK_MoveBackToPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto BossController = Cast<ACPP_AIBossController>(OwnerComp.GetAIOwner());
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(BackLocation.SelectedKeyName, BossController->GetStartLocation());
	return EBTNodeResult::InProgress;
}

void UTK_MoveBackToPosition::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (ShouldAbortMove(OwnerComp))
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

bool UTK_MoveBackToPosition::ShouldAbortMove(const UBehaviorTreeComponent& OwnerComp)
{
	auto BossController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner());
	if (BossController->GetTarget() != nullptr)
		return true;
	return false;
}