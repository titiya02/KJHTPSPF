// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_PatrolComponent.generated.h"

class ACPP_PatrolRoute;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KJHTPSPF_API UCPP_PatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	FVector GetWaypoint() const;
	bool IsRouteSet() const;
	void SetIndexToNext();
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	ACPP_PatrolRoute* Route;

	int PointIndex;

	bool bReverse = false;
};
