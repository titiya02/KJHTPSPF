// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_MoveInArea.h"
#include "KJHTPSPF.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Controller/CPP_AIMinionController.h"

UTK_MoveInArea::UTK_MoveInArea()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UTK_MoveInArea::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Type::InProgress;
}

void UTK_MoveInArea::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	FVector Location = FVector();
	if(auto Target = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName)))
		Location = Target->GetActorLocation();
	double Distance = (Location - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()).Length();

	if (Distance <= CanAttackDistance && GetbAttack(OwnerComp))
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	else if (ShouldAbortMove(OwnerComp))
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
}

bool UTK_MoveInArea::ShouldAbortMove(const UBehaviorTreeComponent& OwnerComp)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	FVector Location = Blackboard->GetValueAsVector(StartLocation.SelectedKeyName);
	double Distance = (Location - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()).Length();

	double TraceDistance = Cast<ACPP_AIMinionController>(OwnerComp.GetAIOwner())->GetTraceDistance();
	if (Distance > TraceDistance)
		return true;
	return false;
}

bool UTK_MoveInArea::GetbAttack(const UBehaviorTreeComponent& OwnerComp)
{
	

	auto Blackboard = OwnerComp.GetBlackboardComponent();
	bool bCanAttack = Blackboard->GetValueAsBool(bIsCanAttack.SelectedKeyName);
	return bCanAttack;
}