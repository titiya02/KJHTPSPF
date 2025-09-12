// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "CPP_SV_IsBlockbyStatic.generated.h"

UCLASS()
class KJHTPSPF_API UCPP_SV_IsBlockbyStatic : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	UCPP_SV_IsBlockbyStatic();
protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere)
	FBlackboardKeySelector bIsCanAttackKey;
};
