// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AICharacter.h"
#include "KJHTPSPF.h"
#include "Item/Weapon/CPP_Basegun.h"
#include "Patrol/CPP_PatrolComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/CPP_UserGaugeBar.h"
#include "Controller/CPP_AIMinionController.h"
#include "DrawDebugHelpers.h"

ACPP_AICharacter::ACPP_AICharacter()
{
	AssignDefaultSubobject(PatrolComponent);
	AssignDefaultSubobject(LifeGauge)->SetupAttachment(GetMesh());
}

void ACPP_AICharacter::Reload()
{
	if (WeaponType != ECharacterWeapon::Unknown &&
		CharacterState != ECharacterState::Reloading &&
		CharacterState != ECharacterState::Arming &&
		CharacterState != ECharacterState::Acting &&
		CharacterState != ECharacterState::Died)
	{
		if (auto* Gun = Cast<ACPP_Basegun>(ArmedWeapon))
		{
			NeedBulletQuantity = Gun->NeedBullet();
			FMontageData MontageData = ArmedWeapon->GetMontageData(ECharacterState::Acting, 1);
			PlayAnimMontageData(MontageData);
			Gun->PlayWeaponMontage(2);
			CharacterState = ECharacterState::Reloading;
		}
	}
}

bool ACPP_AICharacter::AIArmingWeapon(int value)
{
	if (value == 0)
	{
		DisArmingWeapon();
		return true;
	}
	else
	{
		ECharacterWeapon SelectedWeapon = static_cast<ECharacterWeapon>(value);
		if (CurrentArmedWeapons.Contains(SelectedWeapon))
			if (*CurrentArmedWeapons.Find(SelectedWeapon) != nullptr)
			{
				CheckWeaponArmed(SelectedWeapon);
				return true;
			}
	}
	return false;
}

void ACPP_AICharacter::Attack()
{
	BeginActionAStarted();
	UAnimInstance* AIAnimInstance = GetMesh()->GetAnimInstance();
	if (AIAnimInstance)
	{
		UAnimMontage* Montage = AIAnimInstance->GetCurrentActiveMontage();
		if (Montage)
		{
			if (WeaponType == ECharacterWeapon::Melee)
			{
				AIAnimInstance->Montage_SetPlayRate(Montage, 0.75);
			}
		}
	}
}

void ACPP_AICharacter::ThrowFlash()
{
	CharacterState = ECharacterState::Acting;
	FMontageData MontageData = Cast<ACPP_BaseWeapon>(GetWeapon(ECharacterWeapon::Grenade))->GetMontageData(ECharacterState::Acting, 0);
	PlayAnimMontageData(MontageData);
}

void ACPP_AICharacter::SetLifeGaugeVisibility(bool Visible)
{
	LifeGauge->SetVisibility(Visible);
}

float ACPP_AICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (auto AIController = Cast<ACPP_AIMinionController>(GetController()))
	{
		APawn* DamagePawn = EventInstigator->GetPawn();
		double Distance = (GetActorLocation() - DamagePawn->GetActorLocation()).Length();
		if(AIController->GetbPatrol() || Distance >= AIController->GetTraceDistance())
			return 0;
	}
	double Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UpdateWidget(CurrentHealthPercent());
	return Damage;
}

void ACPP_AICharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnAIWeapons();
	UpdateWidget(CurrentHealthPercent());
	LifeGauge->SetVisibility(false);
}

void ACPP_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Cast<ACPP_AIController>(GetController())->GetTarget() == nullptr)
	{
		LifeNow += 20 * DeltaTime;
		if (LifeNow >= LifeMax)
			LifeNow = LifeMax;
		UpdateWidget(CurrentHealthPercent());
	}
}

void ACPP_AICharacter::UpdateWidget(double Value)
{
	if(auto LifeBar = Cast<UCPP_UserGaugeBar>(LifeGauge->GetWidget()))
		LifeBar->UpdateGaugeBar(Value);
}

void ACPP_AICharacter::SpawnAIWeapons()
{
	if (IsWeaponSpawned) return;
	IsWeaponSpawned = true;

	FActorSpawnParameters params;

	params.Owner = this;
	params.Instigator = this;

	for (TSubclassOf<ACPP_BaseWeapon> WeaponClass : AIWeaponClasses)
	{
		auto Weapon = Cast<ACPP_BaseWeapon>(GetWorld()->SpawnActor<AActor>(WeaponClass, params));
		Weapon->AttachToComponent
		(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			Weapon->GetSocketOnUnarmed()
		);

		if (CurrentArmedWeapons.Contains(Weapon->GetWeaponType()))
			*CurrentArmedWeapons.Find(Weapon->GetWeaponType()) = Weapon;
		Weapon->SetVisibilityType(true);
	}
}
