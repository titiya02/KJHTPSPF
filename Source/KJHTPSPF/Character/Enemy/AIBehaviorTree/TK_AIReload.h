// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TK_AIReload.generated.h"

/**
 * 
 */
UCLASS()
class KJHTPSPF_API UTK_AIReload : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UTK_AIReload();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
