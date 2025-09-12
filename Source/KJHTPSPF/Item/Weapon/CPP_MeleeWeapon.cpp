// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MeleeWeapon.h"
#include "KJHTPSPF.h"
#include "Engine/DamageEvents.h"

ACPP_MeleeWeapon::ACPP_MeleeWeapon()
{
	AssignDefaultSubobject(MeleeWeaponCapsule)->SetupAttachment(SkeletalMesh);
	WeaponType = ECharacterWeapon::Melee;

	MeleeWeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	MeleeWeaponCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeWeaponCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	MeleeWeaponCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnWeaponBeginOverlap);
}

void ACPP_MeleeWeapon::StartCollisionEnable()
{
	MeleeWeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
}

void ACPP_MeleeWeapon::StopCollisionEnable()
{
	MeleeWeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void ACPP_MeleeWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
											AActor* OtherActor,
											UPrimitiveComponent* OtherComp,
											int32 OtherBodyIndex,
											bool bFromSweep,
											const FHitResult& SweepResult)
{
	if (OtherActor != Owner)
		AddAttackedActor(OtherActor);
}

void ACPP_MeleeWeapon::AddAttackedActor(AActor* OverlappedActor)
{
	if (!OverlappedActors.Contains(OverlappedActor))
	{
		OverlappedActors.Add(OverlappedActor);
		OverlappedActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
	}
}

void ACPP_MeleeWeapon::ClearOverlappedActors()
{
	OverlappedActors.Empty();
}
