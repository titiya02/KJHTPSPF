// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_BossSkill.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KJHTPSPF.h"
#include "Controller/CPP_AIBossController.h"

UTK_BossSkill::UTK_BossSkill()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UTK_BossSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName) == nullptr || SkillNum == 0)
		return EBTNodeResult::Type::Failed;
	
	auto Owner = Cast<ACPP_AIBossController>(OwnerComp.GetAIOwner());
	if (Owner->UseSkill(SkillNum))
		return EBTNodeResult::Type::InProgress;
	return EBTNodeResult::Type::Failed;
	
}

void UTK_BossSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (auto AIController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner()))
		if (AIController->CheckPawnIdle())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}
