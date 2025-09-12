// Fill out your copyright notice in the Description page of Project Settings.


#include "TK_ArmWeapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KJHTPSPF.h"
#include "Controller/CPP_AIController.h"

UTK_ArmWeapon::UTK_ArmWeapon()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UTK_ArmWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(WeaponNum == -1)
		return EBTNodeResult::Failed;

	if (auto AIController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner()))
		if (AIController->AIArmingWeapon(WeaponNum))
			return EBTNodeResult::InProgress;

	return EBTNodeResult::Failed;
}

void UTK_ArmWeapon::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (auto AIController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner()))
		if (AIController->CheckPawnIdle())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

