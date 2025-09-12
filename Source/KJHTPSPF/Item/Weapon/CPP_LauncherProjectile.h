// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BulletProjectile.h"
#include "CPP_LauncherProjectile.generated.h"

class ACPP_ExplosiveEffect;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_LauncherProjectile : public ACPP_BulletProjectile
{
	GENERATED_BODY()
	
	ACPP_LauncherProjectile();
		
protected:
	void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	void Explode();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACPP_ExplosiveEffect> EffectClass;

	UPROPERTY(EditDefaultsOnly)
	double ExplosiveRadius = 0;
};
