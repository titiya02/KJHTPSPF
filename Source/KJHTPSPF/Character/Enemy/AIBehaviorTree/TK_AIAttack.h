// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TK_AIAttack.generated.h"

/**
 * 
 */
UCLASS()
class KJHTPSPF_API UTK_AIAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UTK_AIAttack();
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
};
