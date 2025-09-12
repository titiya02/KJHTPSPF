// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseSkill.h"
#include "CPP_MontageDataAsset.h"

// Sets default values
ACPP_BaseSkill::ACPP_BaseSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_BaseSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_BaseSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FMontageData ACPP_BaseSkill::GetMontageData(int Value) const
{
	if (SkillMontageData)
		return SkillMontageData->GetMontageData(Value);
	return FMontageData();
}

