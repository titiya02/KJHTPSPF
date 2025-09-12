// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_AIAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KJHTPSPF.h"
#include "Controller/CPP_AIController.h"

UTK_AIAttack::UTK_AIAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UTK_AIAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (auto AIController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner()))
		if(AIController->BeginAttack())
			return EBTNodeResult::InProgress;

	return EBTNodeResult::Failed;
}

void UTK_AIAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (auto AIController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner()))
		if (AIController->CheckPawnIdle())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
