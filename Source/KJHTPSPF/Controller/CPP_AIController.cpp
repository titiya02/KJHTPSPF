// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AIController.h"
#include "KJHTPSPF.h"
#include "Character/Enemy/CPP_AICharacter.h"

ACPP_AIController::ACPP_AIController()
{	
	SetGenericTeamId(FGenericTeamId(2));
}

bool ACPP_AIController::ReloadWeapon()
{
	if (auto AI = Cast<ACPP_AICharacter>(GetPawn()))
		if (AI->GetAIType() == EAIType::Boss ||
			AI->GetAIType() == EAIType::Range)
		{
			AI->Reload();
			return true;
		}

	return false;
}

bool ACPP_AIController::BeginAttack()
{
	if (auto AI = Cast<ACPP_AICharacter>(GetPawn()))
	{
		AI->Attack();
		return true;
	}
	return false;
}

bool ACPP_AIController::AIArmingWeapon(int Value)
{
	if (auto AI = Cast<ACPP_AICharacter>(GetPawn()))
		return AI->AIArmingWeapon(Value);
	return false;
}

bool ACPP_AIController::CheckPawnIdle()
{
	if (auto AI = Cast<ACPP_AICharacter>(GetPawn()))
		if (AI->GetAIState() == ECharacterState::Idle)
			return true;
	return false;
}

void ACPP_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Cast<ACPP_AICharacter>(InPawn)->SetGenericTeamId(TeamId);
}

void ACPP_AIController::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(TestKJH, Log, TEXT("%s : %d"), *this->GetName(), TeamId.GetId());

	if (BehaviorTree)
		RunBehaviorTree(BehaviorTree);
}

ETeamAttitude::Type ACPP_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if (OtherAgent)
	{
		auto Attitude = (OtherAgent->GetGenericTeamId() == GetGenericTeamId()) ?
			ETeamAttitude::Friendly : ETeamAttitude::Hostile;
		//UE_LOG(TestKJH, Log, TEXT("Owner : %s, Other %s : , Attitude : %s"), *this->GetName(), *Other.GetName(), *EnumToFName(Attitude).ToString());
		//UE_LOG(TestKJH, Log, TEXT("Owner : %d, Other : %d"), GetGenericTeamId().GetId(), OtherAgent->GetGenericTeamId().GetId());
		return Attitude;
	}

	return ETeamAttitude::Neutral;
}
