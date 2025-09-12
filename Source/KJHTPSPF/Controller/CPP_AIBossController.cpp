// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AIBossController.h"
#include "KJHTPSPF.h"
#include "Character/Enemy/CPP_AIBoss.h"
#include "Character/CPP_Player.h"
#include "CPP_PlayerController.h"
#include "EngineUtils.h"

ACPP_AIBossController::ACPP_AIBossController()
{
}

bool ACPP_AIBossController::UseSkill(int Value)
{
	if (auto AI = Cast<ACPP_AIBoss>(GetPawn()))
		return AI->UseSkill(Value);
	return false;
}

bool ACPP_AIBossController::UseFlashBang()
{
	if (auto AI = Cast<ACPP_AICharacter>(GetPawn()))
	{
		AI->ThrowFlash();
		return true;
	}
	return false;
}

void ACPP_AIBossController::SetTarget(APawn* TargetPawn)
{
	if (TargetPawn != nullptr)
	{
		double BossHealth = Cast<ACPP_AIBoss>(GetPawn())->CurrentHealthPercent();
		auto BossController = Cast<ACPP_PlayerController>(TargetPawn->GetController());
		BossController->GetCanvas()->UpdateBossHealthBarVisibility(true);
		BossController->GetCanvas()->UpdateBossHealthBar(BossHealth);
	}
	else
		if (Target != nullptr)
			Cast<ACPP_PlayerController>(Cast<ACPP_Character>(Target)->GetController())->GetCanvas()->UpdateBossHealthBarVisibility(false);

	Target = TargetPawn;
}

void ACPP_AIBossController::SetStartLocation(FVector Location)
{
	StartLoaction = Location;
}

void ACPP_AIBossController::OnUnPossess()
{
	Super::OnUnPossess();
	Cast<ACPP_PlayerController>(Target->GetInstigatorController())->GetCanvas()->UpdateBossHealthBarVisibility(false);
	Destroy();
}
