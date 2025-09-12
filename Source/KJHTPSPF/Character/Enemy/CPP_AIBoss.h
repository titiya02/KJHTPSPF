// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_AICharacter.h"
#include "BossSkill/CPP_BaseSkill.h"
#include "CPP_AIBoss.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_AIBoss : public ACPP_AICharacter
{
	GENERATED_BODY()
	
public:
	ACPP_AIBoss();

	bool UseSkill(int Value);
	void ActivateSkill();
		
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;	

	float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	void SpawnSkill();
	void ThrowGrenade() override;
	void Died() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ACPP_BaseSkill>> SkillClasses;

	UPROPERTY(VisibleAnywhere)
	TArray<ACPP_BaseSkill*> Skilles;

	int SkillNum = -1;

	bool IsSkillSpawned = false;
};
