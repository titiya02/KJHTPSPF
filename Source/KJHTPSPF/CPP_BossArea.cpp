// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BossArea.h"
#include "Components/BoxComponent.h"
#include "Character/CPP_Player.h"
#include "Controller/CPP_AIBossController.h"
#include "KJHTPSPF.h"

ACPP_BossArea::ACPP_BossArea()
{
	SetRootComponent(AssignDefaultSubobject(BossAreaBox));
}

void ACPP_BossArea::BeginPlay()
{
	Super::BeginPlay();
	BossAreaBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBossAreaBoxBeginOverlap);
	BossAreaBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnBossAreaBoxEndOverlap);
}

void ACPP_BossArea::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	BossAreaBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnBossAreaBoxBeginOverlap);
	BossAreaBox->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnBossAreaBoxEndOverlap);
}

void ACPP_BossArea::OnBossAreaBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (auto PlayerPawn = Cast<ACPP_Player>(OtherActor))
	{
		if (auto BossController = Cast<ACPP_AIBossController>(Boss->GetController()))
			BossController->SetTarget(PlayerPawn);
	}
}

void ACPP_BossArea::OnBossAreaBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (auto PlayerPawn = Cast<ACPP_Player>(OtherActor))
	{
		if(auto BossController = Cast<ACPP_AIBossController>(Boss->GetController()))
			BossController->SetTarget(nullptr);
	}
}

