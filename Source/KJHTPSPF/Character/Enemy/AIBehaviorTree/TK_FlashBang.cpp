// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_FlashBang.h"
#include "KJHTPSPF.h"
#include "Controller/CPP_AIBossController.h"

EBTNodeResult::Type UTK_FlashBang::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto AIController = Cast<ACPP_AIBossController>(OwnerComp.GetAIOwner());
	if(AIController->UseFlashBang())
		return EBTNodeResult::Succeeded;

	return EBTNodeResult::Failed;
}
