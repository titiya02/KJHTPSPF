// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CPP_AIController.generated.h"


UCLASS(Abstract)
class KJHTPSPF_API ACPP_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ACPP_AIController();	

	AActor* GetTarget() const { return Target; };

	bool ReloadWeapon();
	
	bool BeginAttack();
	
	bool AIArmingWeapon(int Value);
	bool CheckPawnIdle();

	FGenericTeamId GetGenericTeamId() const override { return TeamId; }
protected:
	void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	void SetGenericTeamId(const FGenericTeamId& NewTeamId) override { TeamId = NewTeamId; }
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere)
	AActor* Target;
	
	UPROPERTY(EditDefaultsOnly)
	FGenericTeamId TeamId;
};
