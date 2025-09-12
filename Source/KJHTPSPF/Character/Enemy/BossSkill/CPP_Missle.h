// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Missle.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class ACPP_ExplosiveEffect;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Missle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Missle();

	void SetEndLocationAndDamage(FVector Location, float GetDamage);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Explode();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* Projectile;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* ProjectileCollision;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* Trail;

	FVector EndLocation;
	FVector LerpLocation;

	UPROPERTY(VisibleAnywhere)
	FVector TrackingLocation;

	double LerpTick = 0;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACPP_ExplosiveEffect> EffectClass;

	float Damage = 0;

	UPROPERTY(EditDefaultsOnly)
	float ExplosiveRadius = 0;
};
