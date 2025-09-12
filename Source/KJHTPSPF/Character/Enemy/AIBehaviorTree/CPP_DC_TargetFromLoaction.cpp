// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DC_TargetFromLoaction.h"
#include "KJHTPSPF.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Controller/CPP_AIMinionController.h"

bool UCPP_DC_TargetFromLoaction::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	FVector PLocation = Blackboard->GetValueAsVector(Location.SelectedKeyName);
	FVector TLocation = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName))->GetActorLocation();

	double TraceDistance = Cast<ACPP_AIMinionController>(OwnerComp.GetAIOwner())->GetTraceDistance();
	//UE_LOG(TestKJH, Log, TEXT("%f"), (PLocation - TLocation).Length());

	if ((PLocation - TLocation).Length() > TraceDistance)
		return true;
	return false;
}
