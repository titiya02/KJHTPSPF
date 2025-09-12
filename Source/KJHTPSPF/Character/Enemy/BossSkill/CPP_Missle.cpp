// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Missle.h"
#include "KJHTPSPF.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Item/Weapon/CPP_ExplosiveEffect.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACPP_Missle::ACPP_Missle()
{
 	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(AssignDefaultSubobject(Mesh));
	AssignDefaultSubobject(ProjectileCollision)->SetupAttachment(Mesh);
	AssignDefaultSubobject(Trail)->SetupAttachment(Mesh);
	AssignDefaultSubobject(Projectile);

}

void ACPP_Missle::SetEndLocationAndDamage(FVector Location, float GetDamage)
{
	EndLocation = Location;
	LerpLocation = GetActorForwardVector() * (GetActorLocation() - Location).Length();
	Damage = GetDamage;
}

// Called when the game starts or when spawned
void ACPP_Missle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_Missle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((GetActorLocation() - EndLocation).Length() < 30)
		Explode();

	if (LerpTick < 1)
	{
		TrackingLocation = FMath::Lerp(LerpLocation, EndLocation ,LerpTick);
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TrackingLocation));
		Projectile->Velocity = Projectile->InitialSpeed * UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TrackingLocation).Quaternion().GetForwardVector();
		LerpTick += DeltaTime * 0.5;
	}
}

void ACPP_Missle::Explode()
{
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Owner);
	IgnoreActors.Add(GetInstigator());

	UGameplayStatics::ApplyRadialDamageWithFalloff
	(
		this,
		Damage,
		1,
		GetActorLocation(),
		(ExplosiveRadius / 2),
		ExplosiveRadius,
		1,
		UDamageType::StaticClass(),
		IgnoreActors,
		this,
		GetInstigatorController()
	);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosiveRadius, 10, FColor::Red, false, 5);

	GetWorld()->SpawnActor<AActor>(EffectClass, GetActorTransform());
	Destroy();
}

