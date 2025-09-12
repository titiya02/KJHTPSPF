// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CPP_Character.h"
#include "CPP_AICharacter.generated.h"

class UCPP_PatrolComponent;
class UWidgetComponent;

UENUM(BlueprintType)
enum class EAIType : uint8
{
	Unknown,
	Melee,
	Range,
	Boss
};
UCLASS(Abstract)
class KJHTPSPF_API ACPP_AICharacter : public ACPP_Character
{
	GENERATED_BODY()

public:
	ACPP_AICharacter();

	void Reload() override;

	EAIType GetAIType() const { return AIType; };
	ECharacterState GetAIState() const { return CharacterState; };
	
	bool AIArmingWeapon(int value);
	void Attack();
	void ThrowFlash();

	void SetLifeGaugeVisibility(bool Visible);

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void UpdateWidget(double Value);
private:
	void SpawnAIWeapons();
protected:
	UPROPERTY(EditDefaultsOnly)
	EAIType AIType = EAIType::Unknown;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ACPP_BaseWeapon>> AIWeaponClasses;

	UPROPERTY(EditDefaultsOnly)
	UCPP_PatrolComponent* PatrolComponent;

	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* LifeGauge;

	bool IsWeaponSpawned = false;
};
