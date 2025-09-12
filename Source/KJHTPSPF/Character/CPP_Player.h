// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Character.h"
#include "Components/TimelineComponent.h"
#include "CPP_Player.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPostProcessComponent;
class ACPP_Inventory;
class ACPP_PlayerController;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Player : public ACPP_Character
{
	GENERATED_BODY()

public:
	ACPP_Player();

	void SetController(AController* OnwerController);
	
	bool GetIsAiming() const { return bIsAiming; };
	bool GetIsDriving() const { return bIsDriving; };
	bool GetRunning() const { return bIsRun; };

	void RunTrigger();

	void BeginWeaponA() override;
	void BeginWeaponB() override;
	void BeginWeaponC() override;
	void BeginWeaponD() override;

	void BeginActionBStarted();
	void BeginActionBCompleted();

	void OnAiming(int intPerson);
	void OffAiming();

	void BeginItemInteraction(ACPP_Item* InteractionActor);
	void Reload() override;
	void ReloadBullet(int Quantity) override;

	void MachinegunAuto();

	void UseMedicalkit();
	void GainHealth();

	void ChangeWeapon();

	void ThrowGrenade() override;
	void HitFlashBang(double Time = 1.0f);
	
	void SetIsFront(bool Value) { bIsWalkingFront = Value; };

	TArray<ACPP_BaseWeapon*> GetAllWeapons() const;
	ACPP_Inventory* GetInventory() const;
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

	void ArmingWeapon(ECharacterWeapon Type) override;
	void DisArmingWeapon() override;

	void PlayFlashBangTimer();

	UFUNCTION()
	void TimeLineFirstUpdate(float DeltaTime);

	UFUNCTION()
	void TimeLineThirdUpdate(float DeltaTime);

	UFUNCTION()
	void FlashTimeLineBang(float DeltaTime);

private:
	void BeginActionAStarted() override;	
	void BeginActionACompleted() override;

	void PlayFAMeshMontage();

	void HideBoneAndChildren(FName ParentBoneName);
	void UnHideBoneAndChildren(FName ParentBoneName);

protected:
	UPROPERTY(VisibleDefaultsOnly)
	ACPP_PlayerController* PlayerController;

	UPROPERTY(VisibleDefaultsOnly)
	TMap<ECharacterWeapon, USkeletalMeshComponent*> FAGunMeshs;

	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterWeapon, UAnimMontage*> FAGunMontages;

	UPROPERTY(VisibleDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
	UPostProcessComponent* PostProcess;

	UPROPERTY(EditDefaultsOnly)
	UMaterialParameterCollection* MPC_FlashBang;

	UPROPERTY(VisibleInstanceOnly)
	ACPP_Inventory* Inventory = nullptr;

	FTimeline ZoomTimeLineFirst;

	FTimeline ZoomTimeLineThird;

	FTimeline FlashTimeLine;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* CurveFlash;

	UPROPERTY(EditAnywhere)
	UCurveFloat* TimeLineFOV;

	UPROPERTY(EditAnywhere)
	UCurveFloat* TimeLineTargetArmFirst;

	UPROPERTY(EditAnywhere)
	UCurveFloat* TimeLineTargetArmThird;

	UPROPERTY(EditAnywhere)
	UCurveVector* TimeLineOffsetFirst;

	UPROPERTY(EditAnywhere)
	UCurveVector* TimeLineOffsetThird;

	UPROPERTY(VisibleAnywhere)
	int CurrentAiming = 0;

	UPROPERTY(VisibleDefaultsOnly)
	bool bIsRun = false;

	UPROPERTY(VisibleDefaultsOnly)
	bool bIsWalkingFront = false;

	UPROPERTY(VisibleDefaultsOnly)
	bool bIsDriving = false;

	UPROPERTY(VisibleDefaultsOnly)
	bool bIsAiming = false;

	FTimerHandle FlashBangTimer;
};
