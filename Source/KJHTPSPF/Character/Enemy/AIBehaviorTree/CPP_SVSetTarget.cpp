// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SVSetTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Controller/CPP_AIMinionController.h"
#include "DrawDebugHelpers.h"

void UCPP_SVSetTarget::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
	auto Blackboard = SearchData.OwnerComp.GetBlackboardComponent();
	auto Target = Cast<ACPP_AIController>(SearchData.OwnerComp.GetAIOwner())->GetTarget();
	
	if (Blackboard->GetValueAsObject(TargetKey.SelectedKeyName) == nullptr && Target != nullptr)
	{
		Blackboard->SetValueAsObject(TargetKey.SelectedKeyName, Target);
		Blackboard->SetValueAsVector(PerceptionLocation.SelectedKeyName, SearchData.OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
		/*DrawDebugSphere(
			GetWorld(),
			SearchData.OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(),
			Cast<ACPP_AIMinionController>(SearchData.OwnerComp.GetAIOwner())->GetTraceDistance(),
			50,
			FColor::Red,
			false,
			100,
			0,
			1
		);*/
	}
	else if (Blackboard->GetValueAsObject(TargetKey.SelectedKeyName) != nullptr && Target == nullptr)
	{
		Blackboard->ClearValue(TargetKey.SelectedKeyName);
		Blackboard->ClearValue(PerceptionLocation.SelectedKeyName);
	}
}
