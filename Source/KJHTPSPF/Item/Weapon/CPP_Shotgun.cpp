// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Shotgun.h"
#include "KJHTPSPF.h"

ACPP_Shotgun::ACPP_Shotgun()
{
	MaxBullet = 4;
	BulletVelocity = 1200;
}

// 샷건은 12발의 총알이 전방방향 기준 1도 내부적으로 랜덤한 방향으로 발사
void ACPP_Shotgun::FireBullet()
{
	Super::FireBullet();
	FVector StartLocation = SkeletalMesh->GetSocketLocation("MuzzleFlash");
	FRotator ForwardRotator = UKismetMathLibrary::FindLookAtRotation(StartLocation, GetProjectileDestination());

	for (int32 i = 0; i < BulletCount; i++)
	{
		FRotator BulletRotator = FRotator(0,0,0);
		double RandomYaw = FMath::RandRange(-SpreadAngle, SpreadAngle);
		double RandomPitch = FMath::RandRange(-SpreadAngle, SpreadAngle);

		BulletRotator += ForwardRotator;
		BulletRotator.Yaw += RandomYaw;
		BulletRotator.Pitch += RandomPitch;

		auto* const Projectile = GetWorld()->SpawnActor<AActor>(BPBulletClass, StartLocation, BulletRotator, SpawnParameters);
	}
}

void ACPP_Shotgun::BeginActionBStarted()
{
	Super::BeginActionBStarted();
}

void ACPP_Shotgun::BeginActionBCompleted()
{
	Super::BeginActionBCompleted();
}

void ACPP_Shotgun::BeginActionAStarted()
{
	if (CurrentBullet == 0) return;
	Super::BeginActionAStarted();
	FireBullet();
}

void ACPP_Shotgun::BeginActionACompleted()
{
	Super::BeginActionACompleted();
}
