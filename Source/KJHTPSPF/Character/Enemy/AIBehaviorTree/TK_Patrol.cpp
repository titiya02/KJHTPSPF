// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_Patrol.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/CPP_AICharacter.h"
#include "AIController.h"
#include "../Patrol/CPP_PatrolComponent.h"
#include "KJHTPSPF.h"
#include "Navigation/PathFollowingComponent.h"

EBTNodeResult::Type UTK_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (auto AI = Cast<ACPP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		PatrolComponent = AI->GetComponentByClass<UCPP_PatrolComponent>();
		if (!IsValid(PatrolComponent)) return EBTNodeResult::Failed;
		else if(!PatrolComponent->IsRouteSet()) return EBTNodeResult::Failed;

		auto returnValue = OwnerComp.GetAIOwner()->MoveToLocation(PatrolComponent->GetWaypoint(), AcceptableRadius);

		switch (returnValue)
		{
		case EPathFollowingRequestResult::Failed:
			return EBTNodeResult::Failed;
		case EPathFollowingRequestResult::AlreadyAtGoal:
			PatrolComponent->SetIndexToNext();
			[[fallthrough]];
		case EPathFollowingRequestResult::RequestSuccessful:
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
