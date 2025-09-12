// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AIMinionController.h"
#include "KJHTPSPF.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "Character/Enemy/CPP_AICharacter.h"
#include "CPP_PlayerController.h"

ACPP_AIMinionController::ACPP_AIMinionController()
{
	PrimaryActorTick.bCanEverTick = true;

	AssignDefaultSubobject(AIPerception);

	AssignDefaultSubobject(SenseSight);
	SenseSight->SightRadius = 1000;
	SenseSight->LoseSightRadius = 1200;
	SenseSight->PeripheralVisionAngleDegrees = 60;
	SenseSight->SetMaxAge(5.0);
	SenseSight->DetectionByAffiliation.bDetectEnemies = true;
	SenseSight->DetectionByAffiliation.bDetectNeutrals = true;
	SenseSight->DetectionByAffiliation.bDetectFriendlies = false;

	AssignDefaultSubobject(SenseHearing);
	SenseHearing->HearingRange = 1500;
	SenseHearing->SetMaxAge(5.0);
	SenseHearing->DetectionByAffiliation.bDetectEnemies = true;
	SenseHearing->DetectionByAffiliation.bDetectNeutrals = true;
	SenseHearing->DetectionByAffiliation.bDetectFriendlies = false;

	AssignDefaultSubobject(SenseDamage);
	SenseDamage->SetMaxAge(5.0);
	
	AIPerception->ConfigureSense(*SenseSight);
	AIPerception->ConfigureSense(*SenseHearing);
	AIPerception->ConfigureSense(*SenseDamage);

	AIPerception->SetDominantSense(SenseSight->GetSenseImplementation());
}

void ACPP_AIMinionController::BackToPatrol(FVector Location)
{
	bBackToPatrol = true;
	returnLocation = Location;
	Target = nullptr;
}

void ACPP_AIMinionController::BeginPlay()
{
	Super::BeginPlay();
	AIPerception->OnTargetPerceptionInfoUpdated.AddDynamic(this, &ThisClass::OnPerceptionInfoUpdate);

}

void ACPP_AIMinionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bBackToPatrol)
	{
		if ((returnLocation - GetPawn()->GetActorLocation()).Length() < AllowLength)
			bBackToPatrol = false;
	}
}

void ACPP_AIMinionController::OnPerceptionInfoUpdate(const FActorPerceptionUpdateInfo& Info)
{
	if (bBackToPatrol) return;
	AActor* PerceivedActor = Info.Target.Get();
	FName Sensename = Info.Stimulus.Type.Name;

	if (PerceivedActor == nullptr) return;
	/*UE_LOG(TestKJH, Log, TEXT("Sense : %s"), *Sensename.ToString());
	UE_LOG(TestKJH, Log, TEXT("PerceptionActor : %s"), *PerceivedActor->GetName());*/

	if (PerceivedActor->Implements<UGenericTeamAgentInterface>())
	{
		if (GetTeamAttitudeTowards(*PerceivedActor) == ETeamAttitude::Hostile)
		{
			Target = PerceivedActor;
			Cast<ACPP_AICharacter>(GetPawn())->SetLifeGaugeVisibility(true);
		}
		//UE_LOG(TestKJH, Log, TEXT("PerceptionActor : %s"), *PerceivedActor->GetName());
	}
	else
	{
		if (auto AIController = Cast<AAIController>(PerceivedActor->GetInstigatorController()))
		{
			if (GetTeamAttitudeTowards(*AIController) == ETeamAttitude::Hostile)
			{
				Target = PerceivedActor;
				Cast<ACPP_AICharacter>(GetPawn())->SetLifeGaugeVisibility(true);
			}
			//UE_LOG(TestKJH, Log, TEXT("PerceptionActor : %s"), *PerceivedActor->GetName());
		}
	}

	
	
}
