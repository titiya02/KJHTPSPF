// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_AIController.h"
#include "CPP_AIMinionController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;
struct FActorPerceptionUpdateInfo;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_AIMinionController : public ACPP_AIController
{
	GENERATED_BODY()
public:
	ACPP_AIMinionController();

	void BackToPatrol(FVector Location);

	bool GetbPatrol() const { return bBackToPatrol; };
	double GetTraceDistance() const { return TraceDistance; };
protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPerceptionInfoUpdate(const FActorPerceptionUpdateInfo& Info);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditDefaultsOnly)
	UAISenseConfig_Sight* SenseSight; 

	UPROPERTY(EditDefaultsOnly)
	UAISenseConfig_Hearing* SenseHearing;

	UPROPERTY(EditDefaultsOnly)
	UAISenseConfig_Damage* SenseDamage;

	UPROPERTY(VisibleAnywhere)
	TMap<int, AActor*> PercievedActors;

	UPROPERTY(EditDefaultsOnly)
	double AllowLength = 200;

	UPROPERTY(EditDefaultsOnly)
	double TraceDistance = 1500;

	bool bBackToPatrol = false;
	FVector returnLocation;
};
