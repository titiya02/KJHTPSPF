// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_MoveToMelee.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KJHTPSPF.h"
#include "Controller/CPP_AIController.h"

UTK_MoveToMelee::UTK_MoveToMelee()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UTK_MoveToMelee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::InProgress;
}

void UTK_MoveToMelee::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (ShouldAbortMove(OwnerComp))
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
}

bool UTK_MoveToMelee::ShouldAbortMove(const UBehaviorTreeComponent& OwnerComp)
{
	auto AI = OwnerComp.GetAIOwner()->GetPawn();
	auto Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	
	if (Target == nullptr) return true;
	double Distance = (AI->GetActorLocation() - Target->GetActorLocation()).Length();
	if (Distance > abortLength || MeleeAttackLength > Distance)
		return true;
	return false;
}
