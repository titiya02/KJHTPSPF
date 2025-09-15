// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Character.h"
#include "KJHTPSPF.h"
#include "Components/CapsuleComponent.h"
#include "Item/Weapon/CPP_Machinegun.h"
#include "Item/Weapon/CPP_MeleeWeapon.h"
#include "Item/CPP_Bullet.h"
#include "Perception/AISense_Damage.h"
#include "Controller/CPP_PlayerController.h"

// Sets default values
ACPP_Character::ACPP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	bUseControllerRotationYaw = false;

	GetMesh()->SetGenerateOverlapEvents(true);

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;	
	GetCharacterMovement()->MaxWalkSpeed = 300;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150;
}

// Called when the game starts or when spawned
void ACPP_Character::BeginPlay()
{
	Super::BeginPlay();
	if (CharacterState == ECharacterState::Died)
		Destroy();
	LifeNow = LifeMax;
	FLinearColor Red(1.2f, 0.3f, 0.3f);
	for (auto Material : GetMesh()->GetMaterials())
	{
		OriginMaterials.Add(Material);
		UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(Material, this);
		MID->SetVectorParameterValue(TEXT("Tint"), Red);
		HitMaterials.Add(MID);
	}

	TimerDel_Material.BindUFunction(this, TEXT("MaterialEmmisive"), false);

	//UE_LOG(TestKJH, Log, TEXT("%s : %s"), *GetName(), *GetLevel()->GetOuter()->GetName());
}

// Called every frame
void ACPP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

double ACPP_Character::CurrentHealthPercent()
{
	return LifeNow / LifeMax;
}

float ACPP_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//UE_LOG(TestKJH, Log, TEXT("Damageda : %f"), x);
	//UE_LOG(TestKJH, Log, TEXT("Damaged : %f"), DamageAmount);
	//UE_LOG(TestKJH, Log, TEXT("Character : %s"), *GetName());
	if(EventInstigator->GetPawn() != nullptr)
		if (this->GetGenericTeamId() == Cast<ACPP_Character>(EventInstigator->GetPawn())->GetGenericTeamId()) return 0;

	if (CharacterState == ECharacterState::Died) return -1;

	UAISense_Damage::ReportDamageEvent(
		GetWorld(),
		this,
		EventInstigator->GetPawn(),
		Damage,
		GetActorLocation(),
		GetActorLocation()
	);

	if (LifeNow <= Damage)
	{
		float temp = LifeNow;
		LifeNow = 0;
		Died();
		return temp;
	}
	else
	{
		LifeNow -= Damage;
		MaterialEmmisive(true);
		GetWorldTimerManager().ClearTimer(Timer_Material);
		GetWorldTimerManager().SetTimer(Timer_Material, TimerDel_Material, 0.3, false);
		return Damage;
	}
}

void ACPP_Character::ArmingWeapon(ECharacterWeapon Type)
{
	if (CharacterState != ECharacterState::Died &&
		CharacterState != ECharacterState::Arming)
	{
		if(CurrentArmedWeapons.Contains(Type))
			if (*CurrentArmedWeapons.Find(Type))
			{
				ArmedWeapon = *CurrentArmedWeapons.Find(Type);
				FMontageData MontageData = ArmedWeapon->GetMontageData(ECharacterState::Arming, 0);
				WeaponType = Type;
				if (MontageData.Montage)
				{
					PlayAnimMontageData(MontageData);
					CharacterState = ECharacterState::Arming;
				}
			}
	}
}

void ACPP_Character::DisArmingWeapon()
{
	if (CharacterState != ECharacterState::Died &&
		CharacterState != ECharacterState::Arming)
	{
		FMontageData MontageData = ArmedWeapon->GetMontageData(ECharacterState::Arming, 1);
		PlayAnimMontageData(MontageData);
		CharacterState = ECharacterState::Arming;
	}
}

void ACPP_Character::BeginWeaponA()
{
	CheckWeaponArmed(ECharacterWeapon::Machinegun);
}

void ACPP_Character::BeginWeaponB()
{
	CheckWeaponArmed(ECharacterWeapon::Shotgun);
}

void ACPP_Character::BeginWeaponC()
{
	CheckWeaponArmed(ECharacterWeapon::Melee);
}

void ACPP_Character::BeginWeaponD()
{
	CheckWeaponArmed(ECharacterWeapon::Grenade);
}

void ACPP_Character::ThrowGrenade()
{
}

void ACPP_Character::BeginActionAStarted()
{
	if (ArmedWeapon && 
	    (CharacterState != ECharacterState::Arming) &&
		(CharacterState != ECharacterState::Reloading) &&
		(CharacterState != ECharacterState::Acting) &&
		(CharacterState != ECharacterState::Died))
	{
		if (auto* Gun = Cast<ACPP_Basegun>(ArmedWeapon))
		{
			if (Gun->GetCurrentBullet() == 0) return;
			PlayWeaponActingMontage(0);
		}
		else if (auto* Melee = Cast<ACPP_MeleeWeapon>(ArmedWeapon))
		{
			if (Melee->GetAttackCount() == Melee->GetSizeofMontageMap())
				Melee->SetAtackCount(0);
			PlayWeaponActingMontage(Melee->GetAttackCount());
			Melee->SetAtackCount(Melee->GetAttackCount() + 1);
			
		}
		if (auto* Weapon = Cast<ICPP_ActionInterface>(ArmedWeapon))
			Weapon->BeginActionAStarted();
	}	
}


void ACPP_Character::BeginActionATriggered()
{
	if (ArmedWeapon &&
		(CharacterState != ECharacterState::Arming) &&
		(CharacterState != ECharacterState::Reloading) &&
		(CharacterState == ECharacterState::Acting) &&
		(CharacterState != ECharacterState::Died))
	{
		if (auto* Gun = Cast<ACPP_Machinegun>(ArmedWeapon))
		{
			if (Gun->GetCurrentBullet() == 0 || !Gun->GetCanFire()) return;
			PlayWeaponActingMontage(0);
			if (auto* Weapon = Cast<ICPP_ActionInterface>(ArmedWeapon))
				Weapon->BeginActionAStarted();
		}
	}
}

void ACPP_Character::BeginActionACompleted()
{
	if (ArmedWeapon &&
		(CharacterState != ECharacterState::Arming) &&
		(CharacterState != ECharacterState::Reloading) &&
		(CharacterState != ECharacterState::Acting) &&
		(CharacterState != ECharacterState::Died))
	{
		if (auto* Weapon = Cast<ICPP_ActionInterface>(ArmedWeapon))
			Weapon->BeginActionACompleted();
	}
}

void ACPP_Character::PlayWeaponActingMontage(int Value)
{
	CharacterState = ECharacterState::Acting;
	FMontageData MontageData = ArmedWeapon->GetMontageData(ECharacterState::Acting, Value);
	PlayAnimMontageData(MontageData);
}

void ACPP_Character::Died()
{
	CharacterState = ECharacterState::Died;
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	SetLifeSpan(5);

	TArray<ACPP_BaseWeapon*> weapons;
	CurrentArmedWeapons.GenerateValueArray(weapons);

	for (ACPP_BaseWeapon* weapon : weapons)
	{
		if (weapon != nullptr)
			weapon->SetLifeSpan(5);
	}
}

void ACPP_Character::MaterialEmmisive(bool isHitted)
{
	if (isHitted) // 피격시 붉게
		for (int i = 0; i < HitMaterials.Num(); i++)
			GetMesh()->SetMaterial(i, HitMaterials[i]);
	else // 원상복구
		for (int i = 0; i < OriginMaterials.Num(); i++)
			GetMesh()->SetMaterial(i, OriginMaterials[i]);
}

void ACPP_Character::CheckWeaponArmed(ECharacterWeapon Type)
{
	if (WeaponType == ECharacterWeapon::Unknown)
	{
		ArmingWeapon(Type);
	}
	else if (WeaponType != Type)
	{
		DisArmingWeapon();
		ChangeWeaponType = Type;
		bChangeWeapon = true;
	}
	else
		DisArmingWeapon();
}

void ACPP_Character::EquipWeapon()
{
	ArmedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, ArmedWeapon->GetSocketOnArmed());
	ArmedWeapon->UpdateWeaponUI();
	CharacterState = ECharacterState::Idle;
}

void ACPP_Character::UnequipWeapon()
{
	ArmedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, ArmedWeapon->GetSocketOnUnarmed());
	WeaponType = ECharacterWeapon::Unknown;
	CharacterState = ECharacterState::Idle;
	ArmedWeapon = nullptr;
	if (auto PlayerController = Cast<ACPP_PlayerController>(GetController()))
		PlayerController->GetCanvas()->UpdateWeaponUI();
}

void ACPP_Character::ReloadBullet(int Quantity)
{
	if (auto* Gun = Cast<ACPP_Basegun>(ArmedWeapon))
		Gun->SetCurrentBullet(Quantity);
}

void ACPP_Character::SetStateIdle()
{
	CharacterState = ECharacterState::Idle;
}

ECharacterWeapon ACPP_Character::GetWeaponType()
{
	return WeaponType;
}

AActor* ACPP_Character::GetWeapon(ECharacterWeapon Type)
{
	if(CurrentArmedWeapons.Contains(Type) && CharacterState != ECharacterState::Died)
		if (CurrentArmedWeapons.Find(Type))
			return (*CurrentArmedWeapons.Find(Type));
	return nullptr;
}

void ACPP_Character::BeginItemAction()
{
}


