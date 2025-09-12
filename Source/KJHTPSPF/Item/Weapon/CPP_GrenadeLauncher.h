// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Basegun.h"
#include "CPP_GrenadeLauncher.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_GrenadeLauncher : public ACPP_Basegun
{
	GENERATED_BODY()

	ACPP_GrenadeLauncher();

public:
	void FireBullet() override;

	void BeginActionBStarted() override;
	void BeginActionBCompleted() override;
protected:
	void BeginActionAStarted() override;
	void BeginActionACompleted() override;
};
