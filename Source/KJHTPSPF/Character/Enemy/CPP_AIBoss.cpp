// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AIBoss.h"
#include "KJHTPSPF.h"
#include "Item/Weapon/CPP_Grenade.h"
#include "Controller/CPP_AIBossController.h"
#include "Controller/CPP_PlayerController.h"

ACPP_AIBoss::ACPP_AIBoss()
{
	AIType = EAIType::Boss;
	PrimaryActorTick.bCanEverTick = true;
}

bool ACPP_AIBoss::UseSkill(int Value)
{
	if (CharacterState == ECharacterState::Died || 
		CharacterState == ECharacterState::Acting)
		return false;
	if (Skilles.Num() >= Value)
	{
		CharacterState = ECharacterState::Acting;
		PlayAnimMontageData(Skilles[Value - 1]->GetMontageData(0));
		SkillNum = Value - 1;
		return true;
	}
	return false;
}

void ACPP_AIBoss::ActivateSkill()
{
	Skilles[SkillNum]->Activate();
	SkillNum = -1;
}

void ACPP_AIBoss::BeginPlay()
{
	Super::BeginPlay();
	SpawnSkill();
	Cast<ACPP_AIBossController>(GetController())->SetStartLocation(GetActorLocation());
}

void ACPP_AIBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Cast<ACPP_AIController>(GetController())->GetTarget() == nullptr && LifeNow < LifeMax)
		LifeNow = LifeMax;
}

float ACPP_AIBoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (auto PlayerController = Cast<ACPP_PlayerController>(EventInstigator))
		PlayerController->GetCanvas()->UpdateBossHealthBar(LifeNow / LifeMax);
	return Damage;
}

void ACPP_AIBoss::SpawnSkill()
{
	if (IsSkillSpawned) return;
	IsSkillSpawned = true;

	if (SkillClasses.Num() != 0)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = this;

		for (TSubclassOf<ACPP_BaseSkill> SkillClass : SkillClasses)
		{
			auto Skill = GetWorld()->SpawnActor<AActor>(SkillClass, SpawnParameters);
			Skill->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			Skilles.Add(Cast<ACPP_BaseSkill>(Skill));
		}
	}
}

void ACPP_AIBoss::ThrowGrenade()
{
	Super::ThrowGrenade();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = this;
	SpawnParameters.Owner = this;

	if (CurrentArmedWeapons.Contains(ECharacterWeapon::Grenade))
	{
		auto Grenade = Cast<ACPP_Grenade>(
			GetWorld()->SpawnActor<AActor>
			(
				(*CurrentArmedWeapons.Find(ECharacterWeapon::Grenade))->GetClass(),
				GetActorLocation() + GetActorForwardVector() * 50,
				GetActorForwardVector().Rotation(),
				SpawnParameters
			)
		);
		Grenade->StartedThrow();
	}	
}

void ACPP_AIBoss::Died()
{
	Super::Died();
	for (auto Skill : Skilles)
		Skill->SetLifeSpan(5);

}
