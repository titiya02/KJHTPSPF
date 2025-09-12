// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "CPP_DC_IsGunEmpty.generated.h"

/**
 * 
 */
UCLASS()
class KJHTPSPF_API UCPP_DC_IsGunEmpty : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
