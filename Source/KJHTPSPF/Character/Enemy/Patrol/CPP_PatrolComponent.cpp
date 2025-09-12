// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PatrolComponent.h"
#include "CPP_PatrolRoute.h"
#include "Components/SplineComponent.h"

FVector UCPP_PatrolComponent::GetWaypoint() const
{
	if(Route != nullptr)
		return Route->GetSpline()->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::Type::World);
	return FVector();
}

bool UCPP_PatrolComponent::IsRouteSet() const
{
	if(Route == nullptr)
		return false;
	return true;
}

void UCPP_PatrolComponent::SetIndexToNext()
{
	if (Route == nullptr) return;

	auto Waypoint = Route->GetSpline();

	if (bReverse)
	{
		PointIndex--;
		if (PointIndex == -1)
		{
			bReverse = false;
			PointIndex += 2;
		}
	}
	else
	{
		PointIndex++;
		if (PointIndex == Waypoint->GetNumberOfSplinePoints())
		{
			if (Waypoint->IsClosedLoop())
				PointIndex = 0;
			else
			{
				PointIndex -= 2;
				bReverse = true;
			}
		}
	}
}

void UCPP_PatrolComponent::BeginPlay()
{
	Super::BeginPlay();
}

