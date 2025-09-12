// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Machinegun.h"
#include "KJHTPSPF.h"

ACPP_Machinegun::ACPP_Machinegun()
{
	MaxBullet = 30;
	GunRPM = 600;
	BulletVelocity = 5000;
}

void ACPP_Machinegun::FireBullet()
{
	Super::FireBullet();
	FVector StartLocation = SkeletalMesh->GetSocketLocation("MuzzleFlash");
	FRotator ForwardRotator = UKismetMathLibrary::FindLookAtRotation(StartLocation, GetProjectileDestination());

	auto* const Projectile = GetWorld()->SpawnActor<AActor>(BPBulletClass, StartLocation, ForwardRotator, SpawnParameters);
}

void ACPP_Machinegun::BeginActionBStarted()
{
	Super::BeginActionBStarted();
}

void ACPP_Machinegun::BeginActionBCompleted()
{
	Super::BeginActionBCompleted();
}

void ACPP_Machinegun::SetIsAuto()
{
	bIsAuto = !bIsAuto;
}

void ACPP_Machinegun::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Machinegun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FireDelay < 60 / GunRPM)
		FireDelay += DeltaTime;
	if (Owner)
		if (bIsAuto && bIsActionAClicked)
			bCanFire = true;
}

void ACPP_Machinegun::BeginActionAStarted()
{
	bIsActionAClicked = true;
	GunFire();
	bCanFire = false;
}

void ACPP_Machinegun::BeginActionACompleted()
{
	bIsActionAClicked = false;
	Super::BeginActionACompleted();
	bCanFire = false;
}

void ACPP_Machinegun::GunFire()
{
	if (FireDelay >= 60 / GunRPM)
	{
		if (CurrentBullet == 0) return;
		Super::BeginActionAStarted();
		FireBullet();
		FireDelay = 0;
	}
}
