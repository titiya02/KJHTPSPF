// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PatrolRoute.h"
#include "KJHTPSPF.h"
#include "Components/SplineComponent.h"

// Sets default values
ACPP_PatrolRoute::ACPP_PatrolRoute()
{
	SetRootComponent(AssignDefaultSubobject(Waypoint));
}
