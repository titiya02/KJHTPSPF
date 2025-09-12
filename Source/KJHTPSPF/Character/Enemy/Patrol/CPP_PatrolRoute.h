// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_PatrolRoute.generated.h"

class USplineComponent;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_PatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_PatrolRoute();

	USplineComponent* GetSpline() const { return Waypoint; };

protected:
	UPROPERTY(EditAnywhere)
	USplineComponent* Waypoint;
};
