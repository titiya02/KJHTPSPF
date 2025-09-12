// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_AIController.h"
#include "CPP_AIBossController.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_AIBossController : public ACPP_AIController
{
	GENERATED_BODY()
public:
	ACPP_AIBossController();
	
	bool UseSkill(int Value);
	bool UseFlashBang();

	void SetTarget(APawn* TargetPawn);

	FVector GetStartLocation() const { return StartLoaction; };
	void SetStartLocation(FVector Location);

protected:
	void OnUnPossess() override;

protected:
	FVector StartLoaction;
};
