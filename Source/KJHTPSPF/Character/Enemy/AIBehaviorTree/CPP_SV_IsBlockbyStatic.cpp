// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SV_IsBlockbyStatic.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCPP_SV_IsBlockbyStatic::UCPP_SV_IsBlockbyStatic()
{
	bNotifyTick = true;
}

void UCPP_SV_IsBlockbyStatic::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto AI = OwnerComp.GetAIOwner()->GetPawn();
	auto Target = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));

	if (Target == nullptr) return;

	FHitResult Result;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(AI);
		
	bool IsHit = GetWorld()->LineTraceSingleByChannel(
		Result,
		AI->GetActorLocation(),
		Target->GetActorLocation(),
		ECC_Visibility,
		Params
	);

	Blackboard->SetValueAsBool(bIsCanAttackKey.SelectedKeyName, !IsHit);
}
