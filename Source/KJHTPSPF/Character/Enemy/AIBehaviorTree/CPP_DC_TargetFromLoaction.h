// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "CPP_DC_TargetFromLoaction.generated.h"

/**
 * 
 */
UCLASS()
class KJHTPSPF_API UCPP_DC_TargetFromLoaction : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Location;
};
