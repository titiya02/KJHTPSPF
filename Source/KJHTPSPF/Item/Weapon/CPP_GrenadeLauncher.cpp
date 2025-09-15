// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GrenadeLauncher.h"

ACPP_GrenadeLauncher::ACPP_GrenadeLauncher()
{
	MaxBullet = 10;
	BulletVelocity = 600;
}

void ACPP_GrenadeLauncher::FireBullet()
{
	Super::FireBullet();
	FVector StartLocation = SkeletalMesh->GetSocketLocation("MuzzleFlash");
	FRotator ForwardRotator = UKismetMathLibrary::FindLookAtRotation(StartLocation, GetProjectileDestination());

	auto* Projectile = GetWorld()->SpawnActor<AActor>(BPBulletClass, StartLocation, ForwardRotator, SpawnParameters);
	Projectile->Rename();
}

void ACPP_GrenadeLauncher::BeginActionBStarted()
{
	Super::BeginActionBStarted();
}

void ACPP_GrenadeLauncher::BeginActionBCompleted()
{
	Super::BeginActionBCompleted();
}

void ACPP_GrenadeLauncher::BeginActionAStarted()
{
	if (CurrentBullet == 0) return;
	Super::BeginActionAStarted();
	FireBullet();
}

void ACPP_GrenadeLauncher::BeginActionACompleted()
{
	Super::BeginActionACompleted();
}
