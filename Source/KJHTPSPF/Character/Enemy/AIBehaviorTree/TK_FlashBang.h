// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TK_FlashBang.generated.h"

/**
 * 
 */
UCLASS()
class KJHTPSPF_API UTK_FlashBang : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
