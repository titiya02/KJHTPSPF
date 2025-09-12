// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Basegun.h"
#include "KJHTPSPF.h"
#include "../CPP_Bullet.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Character/CPP_Player.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Controller/CPP_AIController.h"
#include "Controller/CPP_PlayerController.h"


ACPP_Basegun::ACPP_Basegun()
{
	AssignDefaultSubobject(MuzzleFlash)->SetupAttachment(SkeletalMesh);
}

void ACPP_Basegun::UpdateWeaponUI()
{
	if (auto PlayerController = Cast<ACPP_PlayerController>(GetInstigatorController()))
	{
		FString Name = StaticEnum<ECharacterWeapon>()->GetNameStringByValue((int64)WeaponType);
		PlayerController->GetCanvas()->UpdateWeaponUI(CurrentBullet, MaxBullet, Name);
	}
}

void ACPP_Basegun::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Basegun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Owner)
	{
		if (bIsAimed && !Cast<ACPP_Player>(Owner)->GetIsAiming())
		{
			ActionBDeltaTime += DeltaTime;
			if (ActionBDeltaTime > 0.1)
			{
				bIsAimed = false;
				Cast<ACPP_Player>(Owner)->OnAiming(3);
			}
		}
	}
}

void ACPP_Basegun::BeginActionBStarted()
{
	Super::BeginActionBStarted();
	bIsAimed = true;
}

void ACPP_Basegun::BeginActionBCompleted()
{
	Super::BeginActionBCompleted();
	if (!Cast<ACPP_Player>(Owner)->GetIsAiming())
		Cast<ACPP_Player>(Owner)->OnAiming(1);
	else
		Cast<ACPP_Player>(Owner)->OffAiming();
	bIsAimed = false;
	ActionBDeltaTime = 0;
}

FVector ACPP_Basegun::GetProjectileDestination()
{
	if (auto* OwnerController = Cast<APlayerController>(GetInstigatorController()))
	{
		FHitResult OutHitResult;
		FVector StartLocation = OwnerController->PlayerCameraManager.Get()->GetCameraLocation();
		FVector EndLocation = OwnerController->PlayerCameraManager.Get()->GetCameraRotation().Quaternion().GetForwardVector()
			* AttackTraceDistance + StartLocation;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(GetOwner());
		
		UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), StartLocation, EndLocation, ObjectTypes,
			false, IgnoreActors, EDrawDebugTrace::None, OutHitResult, true);
		if (OutHitResult.GetActor())
			return OutHitResult.Location;
		else
			return OutHitResult.TraceEnd;
	}
	else if(auto* AIController = Cast<ACPP_AIController>(GetInstigatorController()))
	{
		return AIController->GetTarget()->GetActorLocation();
	}
	else
	{
		UE_LOG(TestKJH, Log, TEXT("GetDestination Error : no Controller"));
		return FVector();
	}
}

void ACPP_Basegun::FireBullet()
{	
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	CurrentBullet--;
	UpdateWeaponUI();
	ApplyRecoil();
}


void ACPP_Basegun::PlayWeaponMontage(int Index) const
{	
	if (IsHidden()) return;
	if (Index < 0)
		Index = 0;
	else if (Index >= GunMontages.Num())
		Index = GunMontages.Num() - 1;
	SkeletalMesh->GetAnimInstance()->Montage_Play(GunMontages[Index]);	
}

void ACPP_Basegun::SetCurrentBullet(int Value)
{
	CurrentBullet = Value;
}

EBulletType ACPP_Basegun::GetBulletType() const
{
	return BulletType;
}

int ACPP_Basegun::NeedBullet()
{
	return MaxBullet - CurrentBullet;
}

int ACPP_Basegun::GetCurrentBullet() const
{
	return CurrentBullet;
}

void ACPP_Basegun::BeginActionAStarted()
{
	Super::BeginActionAStarted();
	PlayWeaponMontage(0);
}

void ACPP_Basegun::BeginActionACompleted()
{
	Super::BeginActionACompleted();
}

void ACPP_Basegun::ApplyRecoil()
{
	float Pitch = RecoilPitch;
	float Yaw = FMath::RandRange(-RecoilYaw, RecoilYaw);

	if (auto PlayerController = Cast<ACPP_PlayerController>(GetInstigatorController()))
	{
		PlayerController->GetRecoil(Pitch, Yaw);
	}
}
