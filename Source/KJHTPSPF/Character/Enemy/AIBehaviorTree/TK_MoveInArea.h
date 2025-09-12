// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "TK_MoveInArea.generated.h"

UCLASS()
class KJHTPSPF_API UTK_MoveInArea : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
	UTK_MoveInArea();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	bool ShouldAbortMove(const UBehaviorTreeComponent& OwnerComp);

private:
	bool GetbAttack(const UBehaviorTreeComponent& OwnerComp);

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector StartLocation;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector bIsCanAttack;

	UPROPERTY(EditAnywhere)
	double CanAttackDistance = 0;
};
