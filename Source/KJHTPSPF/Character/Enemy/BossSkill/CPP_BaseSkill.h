// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_BaseSkill.generated.h"

class UCPP_MontageDataAsset;
struct FMontageData;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_BaseSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_BaseSkill();

	virtual void Activate() {};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FMontageData GetMontageData(int Value) const;
protected:
	UPROPERTY(EditDefaultsOnly)
	UCPP_MontageDataAsset* SkillMontageData;

	UPROPERTY(EditDefaultsOnly)
	double Damage = 0;
};
