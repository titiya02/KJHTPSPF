// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Basegun.h"
#include "CPP_Machinegun.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Machinegun : public ACPP_Basegun
{
	GENERATED_BODY()
	ACPP_Machinegun();

public:
	void FireBullet() override;

	void BeginActionBStarted() override;
	void BeginActionBCompleted() override;

	void SetIsAuto();

	bool GetCanFire() const { return bCanFire; };
protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void BeginActionAStarted() override;
	void BeginActionACompleted() override;

private:
	void GunFire();

protected:
	UPROPERTY(EditAnywhere)
	bool bIsAuto = false;

	UPROPERTY(EditDefaultsOnly)
	double GunRPM = 0;

	bool bIsActionAClicked = false;
	double FireDelay = 0;
	bool bCanFire = true;
};
