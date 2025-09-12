// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseSkill.h"
#include "CPP_LaunchMissle.generated.h"

class ACPP_Missle;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_LaunchMissle : public ACPP_BaseSkill
{
	GENERATED_BODY()
	
public:
	void Activate() override;

private:
	void FireMissle(FVector Location);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACPP_Missle> MissleClass;

	UPROPERTY(EditDefaultsOnly)
	int Misslenum = 3;

	UPROPERTY(EditDefaultsOnly)
	double FireAngle = 45;
};
