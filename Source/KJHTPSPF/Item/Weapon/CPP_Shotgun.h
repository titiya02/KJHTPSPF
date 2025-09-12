// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Basegun.h"
#include "CPP_Shotgun.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Shotgun : public ACPP_Basegun
{
	GENERATED_BODY()
	ACPP_Shotgun();

public:
	void FireBullet() override;

	void BeginActionBStarted() override;
	void BeginActionBCompleted() override;
protected:
	void BeginActionAStarted() override;
	void BeginActionACompleted() override;

private:
	const int32 BulletCount = 12;
	const double SpreadAngle = 1;
};
