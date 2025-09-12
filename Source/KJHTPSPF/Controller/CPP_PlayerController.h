// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "Widget/CPP_UserCanvas.h"
#include "Widget/CPP_UserInventory.h"
#include "CPP_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class ACPP_Player;
struct FInputActionValue;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_PlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	ACPP_PlayerController();

public:
	UCPP_UserCanvas* GetCanvas() { return UserCanvas; };
	UCPP_UserInventory* GetInventory() { return UserInventory; };

	void GetRecoil(float Pitch, float Yaw);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	void SetGenericTeamId(const FGenericTeamId& NewTeamId) override { TeamId = NewTeamId; }
	virtual void OnConstruction(const FTransform& Transform) override;


	void SetupInputComponent() override;
	
	void OnMoveTriggered(const FInputActionValue& Value);
	void OnRunStarted();
	void OnRunCompleted();
	void OnLookTriggered(const FInputActionValue& Value);
	
	void OnCrouchStarted();
	void OnJumpStarted();

	void OnOpenInventoryStarted();
	void OnOpenInventoryCompleted();

	void OnInteractionStarted();

	void OnActionAStarted();
	void OnActionATriggered();
	void OnActionACompleted();

	void OnActionBStarted();
	void OnActionBCompleted();

	void OnReloadTriggered();

	void OnMachinegunAutoStarted();

	void OnUseMedicalkitStarted();

	void OnWeaponAStarted();
	void OnWeaponBStarted();
	void OnWeaponCStarted();
	void OnWeaponDStarted();
private:
	void ViewCenterRayTrace();

	UFUNCTION()
	void ApplyRecoil();
	
private:
	bool bUseTrace = true;
	double TraceDelay = 0;

	FHitResult OutHitResult;
	double InteractionTraceDistance = 500;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACPP_Player> PlayerClass;

	UPROPERTY(VisibleAnywhere)
	ACPP_Player* PlayerPawn;

	FGenericTeamId TeamId;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCPP_UserCanvas> UserCanvasClass;

	UPROPERTY(VisibleAnywhere)
	UCPP_UserCanvas* UserCanvas;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCPP_UserInventory> UserInventoryClass;

	UPROPERTY(VisibleAnywhere)
	UCPP_UserInventory* UserInventory;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	// BaseMove
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Move;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Run;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Look;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Jump;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Parkour;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Crawl;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Crouch;

	// Action
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_OpenInventory;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Interaction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_ActionA;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_ActionB;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_Reload;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_MachinegunAuto;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_UseMedicalkit;

	// Weapon
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_WeaponA;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_WeaponB;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_WeaponC;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_WeaponD;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction_WeaponOnOff;

	float LeftRecoilPitch = 0;
	float LeftRecoilYaw = 0;
	float RecoilDeltaTime = 0.03f;
	float HandlingTime = 0;

	FTimerHandle RecoilHandle;
};
