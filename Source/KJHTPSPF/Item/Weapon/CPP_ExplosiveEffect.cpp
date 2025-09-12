// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ExplosiveEffect.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_ExplosiveEffect::ACPP_ExplosiveEffect()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACPP_ExplosiveEffect::BeginPlay()
{
	Super::BeginPlay();
	
	FFXSystemSpawnParameters SpawnParams
	{
		.WorldContextObject = GetWorld(),
		.SystemTemplate = ExplosiveParticle,
		.Scale = FVector(1,1,1) * ParticleScale,
		.AttachToComponent = RootComponent,
		.LocationType = EAttachLocation::Type::KeepRelativeOffset,
	};

	UNiagaraFunctionLibrary::SpawnSystemAttachedWithParams(SpawnParams);
	UGameplayStatics::PlaySoundAtLocation(this, ExplosiveSound, GetActorLocation(), SoundScale);
	SetLifeSpan(5);
}

// Called every frame
void ACPP_ExplosiveEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

