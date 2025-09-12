// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CPP_SVSetTarget.generated.h"


UCLASS()
class KJHTPSPF_API UCPP_SVSetTarget : public UBTService
{
	GENERATED_BODY()
	
protected:
	void OnSearchStart (FBehaviorTreeSearchData& SearchData) override;

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetKey;

	UPROPERTY(VisibleAnywhere)
	FBlackboardKeySelector PerceptionLocation;
};
