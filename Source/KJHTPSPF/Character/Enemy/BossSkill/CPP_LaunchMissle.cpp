// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LaunchMissle.h"
#include "CPP_Missle.h"
#include "Kismet/KismetMathLibrary.h"
#include "Controller/CPP_AIController.h"

void ACPP_LaunchMissle::Activate()
{
	Super::Activate();
	if(auto Controller = Cast<ACPP_AIController>(GetInstigatorController()))
		if(Controller->GetTarget() != nullptr)
			FireMissle(Controller->GetTarget()->GetActorLocation());
}

void ACPP_LaunchMissle::FireMissle(FVector Location)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FRotator ForwardRotation = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), Location);
	for (int i = 0; i < Misslenum; i++)
	{
		FRotator MissleRotator = FRotator(0, 0, 0);
		
		double RandomYaw = FMath::RandRange(-FireAngle, FireAngle);
		double RandomPitch = FMath::RandRange(0.0, FireAngle*2);

		MissleRotator += ForwardRotation;
		MissleRotator.Yaw += RandomYaw;
		MissleRotator.Pitch += RandomPitch;

		auto Missle = GetWorld()->SpawnActor<AActor>
			(
				MissleClass,
				GetOwner()->GetActorLocation(),
				MissleRotator,
				SpawnParams
			);

		Cast<ACPP_Missle>(Missle)->SetEndLocationAndDamage(Location, Damage);
	}
}
