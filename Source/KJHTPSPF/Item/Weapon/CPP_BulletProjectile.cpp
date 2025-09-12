// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BulletProjectile.h"
#include "KJHTPSPF.h"
#include "CPP_Basegun.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Controller/CPP_AIMinionController.h"

// Sets default values
ACPP_BulletProjectile::ACPP_BulletProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(AssignDefaultSubobject(ProjectileCollision));
	AssignDefaultSubobject(TrailComponent)->SetupAttachment(ProjectileCollision);
	AssignDefaultSubobject(Projectile);
	
	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	
}

// Called when the game starts or when spawned
void ACPP_BulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnProjectileBeginOverlap);
	double Velocity = Cast<ACPP_Basegun>(Owner)->GetBulletVelocity();
	if (auto AI = Cast<ACPP_AIMinionController>(GetInstigator()->GetController()))
		Projectile->Velocity = GetActorForwardVector() * Velocity / 10;
	else 
		Projectile->Velocity = GetActorForwardVector() * Velocity;
	Projectile->ProjectileGravityScale = 0.1;
	if (auto OwnerGun = Cast<ACPP_Basegun>(Owner))
		Damage = OwnerGun->GetDamage();

	FFXSystemSpawnParameters SpawnParams
	{
		.WorldContextObject = GetWorld(),
		.SystemTemplate = TrailComponent->GetFXSystemAsset(),
		.AttachToComponent = GetRootComponent(),
		.LocationType = EAttachLocation::Type::KeepRelativeOffset
	};

	auto const Tracer = UNiagaraFunctionLibrary::SpawnSystemAttachedWithParams(SpawnParams);
	
	SetLifeSpan(10);
}

void ACPP_BulletProjectile::OnProjectileBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	auto Object = OtherComp->GetCollisionObjectType();
	if (Object == ECC_WorldStatic && OtherActor != Owner)
		Destroy();
	else if (Cast<APawn>(OtherActor) && OtherActor != GetInstigator())
	{
		//UE_LOG(TestKJH, Log, TEXT("OtherActor Name : %s"), *OtherActor->GetName());
		if (OtherComp->IsA<USkeletalMeshComponent>())
		{
			double ApplyDamage = Damage;
			if (SweepResult.BoneName.IsEqual("head"))
				ApplyDamage *= 2;
			else if(SweepResult.BoneName.ToString().EndsWith("_l") ||
				    SweepResult.BoneName.ToString().EndsWith("_r"))
				ApplyDamage /= 2;
			OtherActor->TakeDamage(ApplyDamage, FDamageEvent(), GetInstigatorController(), Owner);
			Destroy();
			//UE_LOG(TestKJH, Log, TEXT("OtherActor Skeleton : %s"), *OtherActor->GetName());
		}
	}	
}

// Called every frame
void ACPP_BulletProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator VelocityDirection = GetVelocity().Rotation();

	SetActorRotation(VelocityDirection);
}


