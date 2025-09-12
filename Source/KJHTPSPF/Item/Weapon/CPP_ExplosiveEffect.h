// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_ExplosiveEffect.generated.h"

class UNiagaraSystem;
class USoundCue;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_ExplosiveEffect : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_ExplosiveEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* ExplosiveParticle;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* ExplosiveSound;

	UPROPERTY(EditDefaultsOnly)
	double ParticleScale;

	UPROPERTY(EditDefaultsOnly)
	double SoundScale;
};
