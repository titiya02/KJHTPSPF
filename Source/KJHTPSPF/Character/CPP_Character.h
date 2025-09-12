// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enum/ECharacterWeapon.h"
#include "Interface/CPP_ActionInterface.h"
#include "Enum/ECharacterState.h"
#include "Item/Weapon/CPP_BaseWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CPP_Character.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Character : public ACharacter, public ICPP_ActionInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	double CurrentHealthPercent();

	FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	void SetGenericTeamId(const FGenericTeamId& NewTeamId) override { TeamId = NewTeamId; }

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	void BeginActionATriggered();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECharacterWeapon GetWeaponType();	

	AActor* GetWeapon(ECharacterWeapon Type);

	void BeginItemAction();

	void EquipWeapon();
	void UnequipWeapon();

	virtual void Reload() {};
	virtual void ReloadBullet(int Quantity);
	int	GetNeedBulletQuantity() const { return NeedBulletQuantity; };
	void SetNeedBulletQuantity(int Value = 0) { NeedBulletQuantity = Value; };

	virtual void SetStateIdle();

	virtual void BeginWeaponA();
	virtual void BeginWeaponB();
	virtual void BeginWeaponC();
	virtual void BeginWeaponD();
		
	virtual void ThrowGrenade();

	UFUNCTION()
	void MaterialEmmisive(bool isHitted);

protected:
	virtual void ArmingWeapon(ECharacterWeapon Type);
	virtual void DisArmingWeapon();

	void CheckWeaponArmed(ECharacterWeapon Type);

	void BeginActionAStarted() override;
	void BeginActionACompleted() override;

	void PlayWeaponActingMontage(int Value);

	virtual void Died();

protected:
	FGenericTeamId TeamId;

	UPROPERTY(VisibleInstanceOnly)
	ECharacterState CharacterState = ECharacterState::Idle;

	UPROPERTY(VisibleAnywhere)
	ECharacterWeapon WeaponType = ECharacterWeapon::Unknown;

	UPROPERTY()
	ECharacterWeapon ChangeWeaponType = ECharacterWeapon::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterWeapon, ACPP_BaseWeapon*> CurrentArmedWeapons;

	UPROPERTY(VisibleAnywhere)
	ACPP_BaseWeapon* ArmedWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterState, UCPP_MontageDataAsset*> MontageDataMap;

	UPROPERTY()
	TArray<UMaterialInterface*> OriginMaterials;

	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> HitMaterials;

	FTimerDelegate TimerDel_Material;
	FTimerHandle Timer_Material;

	UPROPERTY(VisibleAnywhere)
	double LifeNow = 0;

	UPROPERTY(EditDefaultsOnly)
	double LifeMax = 100;

	int NeedBulletQuantity = 0;
	bool bChangeWeapon = false;
};