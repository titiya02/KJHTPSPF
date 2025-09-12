// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LauncherProjectile.h"
#include "KJHTPSPF.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CPP_ExplosiveEffect.h"

ACPP_LauncherProjectile::ACPP_LauncherProjectile()
{
	AssignDefaultSubobject(ProjectileMesh)->SetupAttachment(ProjectileCollision);
}

void ACPP_LauncherProjectile::BeginPlay()
{
	Super::BeginPlay();
	Projectile->ProjectileGravityScale = 0.01;
}

void ACPP_LauncherProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Explode();
}

void ACPP_LauncherProjectile::OnProjectileBeginOverlap
(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	auto Object = OtherComp->GetCollisionObjectType();
	if (Object == ECC_WorldStatic && OtherActor != Owner)
		Destroy();
	else if (Cast<APawn>(OtherActor) && OtherActor != GetInstigator())
	{
		if (OtherComp->IsA<USkeletalMeshComponent>())
		{
			Destroy();
		}
	}
}

void ACPP_LauncherProjectile::Explode()
{
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetInstigator());

	UGameplayStatics::ApplyRadialDamageWithFalloff
	(
		this,
		Damage,
		1,
		GetActorLocation(),
		ExplosiveRadius / 2,
		ExplosiveRadius,
		1,
		UDamageType::StaticClass(),
		IgnoreActors,
		this,
		GetInstigatorController()
	);

	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosiveRadius, 10, FColor::Red, false, 5);

	GetWorld()->SpawnActor<AActor>(EffectClass, GetActorLocation(), FRotator());
}
