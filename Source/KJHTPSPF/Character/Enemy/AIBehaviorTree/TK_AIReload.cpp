// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_AIReload.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KJHTPSPF.h"
#include "Controller/CPP_AIController.h"

UTK_AIReload::UTK_AIReload()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UTK_AIReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (auto AIController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner()))
		if (AIController->ReloadWeapon())
			return EBTNodeResult::InProgress;

	return EBTNodeResult::Failed;
}

void UTK_AIReload::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (auto AIController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner()))
		if (AIController->CheckPawnIdle())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
