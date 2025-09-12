// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Grenade.h"
#include "KJHTPSPF.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_ExplosiveEffect.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/OverlapResult.h"
#include "Character/CPP_Player.h"

ACPP_Grenade::ACPP_Grenade()
{
	WeaponType = ECharacterWeapon::Grenade;	
	AssignDefaultSubobject(Projectile);
	
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SkeletalMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	Projectile->bShouldBounce = true;
	Projectile->Velocity = FVector();
	Projectile->bAutoActivate = false;
}

void ACPP_Grenade::StartedThrow()
{
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	SkeletalMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);

	if(auto Player = Cast<ACPP_Player>(GetInstigator()))
		Projectile->Velocity = GetInstigatorController()->GetControlRotation().Quaternion().GetForwardVector() * 600;
	else
		Projectile->Velocity = GetInstigatorController()->GetControlRotation().Quaternion().GetForwardVector() * 200;
	Projectile->ProjectileGravityScale = 0.5;
	Projectile->Activate();
	bIsCharged = true;
}

void ACPP_Grenade::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	if(bIsCharged)
	{
		testTime += Deltatime;
		if (!bIsFlash)
		{
			if (testTime >= 5)
			{
				Explosive();
				testTime = 0;
			}
		}
		else
		{
			if (testTime >= 3)
			{
				Explosive();
				testTime = 0;
			}
		}
		
	}
}

void ACPP_Grenade::BeginActionAStarted()
{
	Super::BeginActionAStarted();
}

void ACPP_Grenade::BeginActionACompleted()
{
	Super::BeginActionACompleted();
}

void ACPP_Grenade::Explosive()
{
	TArray<AActor*> IgnoreActors;
	//IgnoreActors.Add(Owner);
	
	if (!bIsFlash)
	{

		UGameplayStatics::ApplyRadialDamageWithFalloff
		(
			this,
			Damage,
			0,
			GetActorLocation(),
			(ExplosiveRadius / 2),
			ExplosiveRadius,
			5,
			UDamageType::StaticClass(),
			IgnoreActors,
			this,
			GetInstigatorController()
		);

	}
	else
	{
		TArray<FOverlapResult> OverlapResults;
		FCollisionShape Sphere = FCollisionShape::MakeSphere(ExplosiveRadius);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetInstigator());

		if (GetWorld()->OverlapMultiByObjectType(
			OverlapResults,
			GetActorLocation(),
			FQuat::Identity,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
			Sphere,
			Params
		))
		{
			for (const FOverlapResult& result : OverlapResults)
			{
				APawn* OverlappedPawn = Cast<APawn>(result.GetActor());
				USkeletalMeshComponent* mesh = OverlappedPawn->FindComponentByClass<USkeletalMeshComponent>();
				if (mesh == nullptr) continue;
								
				FHitResult hit;
				FCollisionQueryParams TraceParams;
				TraceParams.AddIgnoredActor(this);
				TraceParams.AddIgnoredActor(GetInstigator());
				if (GetWorld()->LineTraceSingleByChannel(
					hit,
					GetActorLocation(),
					mesh->GetBoneLocation("head"),
					ECC_Camera,
					TraceParams
				))
				{
					if (hit.GetActor() == result.GetActor())
					{
						if (auto Player = Cast<ACPP_Player>(OverlappedPawn))
						{
							FVector PawntoFlash = GetActorLocation() - Player->GetActorLocation();
							double dot = FVector::DotProduct(Player->GetActorForwardVector().GetSafeNormal(), PawntoFlash.GetSafeNormal());

							double Distance = PawntoFlash.Length();
							double Time = 0;
							if (Distance <= 200)
								Time = 3;
							else if (Distance <= 500)
								Time = 1.5 * dot;
							else
								Time = 0.1 * dot;

							//UE_LOG(TestKJH, Log, TEXT("TraceResult : %f"), dot);
							Player->HitFlashBang(Time);
						}
					}
				}
			}
		}
	}

	// DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosiveRadius, 10, FColor::Red, false, 5);
	// DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosiveRadius / 4, 10, FColor::Green, false, 5);

	if (EffectClass)
		GetWorld()->SpawnActor<AActor>(EffectClass, GetActorLocation(), FRotator());

	Destroy();
}

