// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "Character/CPP_Player.h"
#include "KJHTPSPF.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Item/CPP_Item.h"
#include "Enum/ECharacterWeapon.h"
#include "Widget/CPP_UserCanvas.h"
#include "Camera/CameraModifier_CameraShake.h"
#include "Item/Weapon/CPP_Basegun.h"
#include "GameFramework/InputSettings.h"
#include "CPP_Inventory.h"
#include "CPP_GameModeBase.h"

ACPP_PlayerController::ACPP_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	SetGenericTeamId(FGenericTeamId(1));
}

void ACPP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceDelay += DeltaTime;
	if (TraceDelay >= 0.1 && bUseTrace)
	{
		TraceDelay = 0;
		ViewCenterRayTrace();
	}
}

void ACPP_PlayerController::GetRecoil(float Pitch, float Yaw)
{
	LeftRecoilPitch += Pitch;
	LeftRecoilYaw = Yaw;

	GetWorld()->GetTimerManager().SetTimer(RecoilHandle, this, &ThisClass::ApplyRecoil, RecoilDeltaTime, true);
}

void ACPP_PlayerController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);	
}

void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UserCanvasClass)
	{
		UserCanvas = CreateWidget<UCPP_UserCanvas>(this, UserCanvasClass);
		if (UserCanvas)
		{
			UserCanvas->AddToViewport();
			UserCanvas->UpdateCrossHairVisible();
			UserCanvas->UpdateWeaponUI();
			UserCanvas->UpdateBossHealthBarVisibility();
		}
	}

	if (UserInventoryClass)
	{
		UserInventory = CreateWidget<UCPP_UserInventory>(this, UserInventoryClass);
		if (UserInventory)
		{
			UserInventory->AddToViewport();
			UserInventory->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	

	if (GetPawn() == nullptr || PlayerClass != nullptr)
	{
		ACPP_GameModeBase* GM = Cast<ACPP_GameModeBase>(GetWorld()->GetAuthGameMode());
		PlayerPawn = GetWorld()->SpawnActor<ACPP_Player>(
			PlayerClass,
			GM->FindPlayerStart(this)->GetActorLocation(),
			GM->FindPlayerStart(this)->GetActorRotation(),
			FActorSpawnParameters()
		);

		Possess(PlayerPawn);
		PlayerPawn->SetController(this);
	}

	// UE_LOG(TestKJH, Log, TEXT("World : %s"), *GetWorld()->GetName());
	// UE_LOG(TestKJH, Log, TEXT("Level : %s"), *GetLevel()->GetName());
	// UE_LOG(TestKJH, Log, TEXT("Outer : %s"), *this->GetOuter()->GetName());
	// UE_LOG(TestKJH, Log, TEXT("Pawn Outer : %s"), *PlayerPawn->GetOuter()->GetName());
}

void ACPP_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//UE_LOG(TestKJH, Log, TEXT("End"));
}

void ACPP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	auto* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (!LocalPlayer) return;

	auto* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!SubSystem) return;

	if (!InputMappingContext) return;
	SubSystem->AddMappingContext(InputMappingContext, 0);

	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) return;

#define BindTriggerAction(Action, Event)\
BindAction(InputAction_##Action, ETriggerEvent::Event, this, &ThisClass::On##Action##Event)
	
	{ // BaseMove
		if (InputAction_Move)
			EnhancedInputComponent->BindTriggerAction(Move, Triggered);

		if (InputAction_Run)
		{
			EnhancedInputComponent->BindTriggerAction(Run, Started);
			EnhancedInputComponent->BindTriggerAction(Run, Completed);
		}

		if (InputAction_Look)
			EnhancedInputComponent->BindTriggerAction(Look, Triggered);

		if (InputAction_Crouch)
			EnhancedInputComponent->BindTriggerAction(Crouch, Started);

		if (InputAction_Jump)
			EnhancedInputComponent->BindTriggerAction(Jump, Started);
	}

	{ // Action
		if (InputAction_OpenInventory)
		{
			EnhancedInputComponent->BindTriggerAction(OpenInventory, Started);
			EnhancedInputComponent->BindTriggerAction(OpenInventory, Completed);
		}

		if(InputAction_Interaction)
			EnhancedInputComponent->BindTriggerAction(Interaction, Started);

		if (InputAction_ActionA)
		{
			EnhancedInputComponent->BindTriggerAction(ActionA, Started);
			EnhancedInputComponent->BindTriggerAction(ActionA, Triggered);
			EnhancedInputComponent->BindTriggerAction(ActionA, Completed);
		}

		if (InputAction_ActionB)
		{
			EnhancedInputComponent->BindTriggerAction(ActionB, Started);
			EnhancedInputComponent->BindTriggerAction(ActionB, Completed);
		}

		if (InputAction_Reload)
			EnhancedInputComponent->BindTriggerAction(Reload, Triggered);

		if(InputAction_MachinegunAuto)
			EnhancedInputComponent->BindTriggerAction(MachinegunAuto, Started);

		if (InputAction_UseMedicalkit)
			EnhancedInputComponent->BindTriggerAction(UseMedicalkit, Started);
	}

	{ // Weapon
		if (InputAction_WeaponA)
			EnhancedInputComponent->BindTriggerAction(WeaponA, Started);

		if (InputAction_WeaponB)
			EnhancedInputComponent->BindTriggerAction(WeaponB, Started);

		if (InputAction_WeaponC)
			EnhancedInputComponent->BindTriggerAction(WeaponC, Started);

		if (InputAction_WeaponD)
			EnhancedInputComponent->BindTriggerAction(WeaponD, Started);
	}
}

void ACPP_PlayerController::OnMoveTriggered(const FInputActionValue& Value)
{
	if (GetPawn() == nullptr) return;
	auto Direction = Value.Get<FVector>();
	auto Rotator = FRotator(0, GetControlRotation().Yaw, 0);
	GetPawn()->AddMovementInput(Rotator.Quaternion() * Direction);
	if (auto CPP_Player = Cast<ACPP_Player>(GetPawn()))
		if (Direction.X >= 0.7)
			CPP_Player->SetIsFront(true);
		else
			CPP_Player->SetIsFront(false);		
}

void ACPP_PlayerController::OnRunStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->RunTrigger();
}

void ACPP_PlayerController::OnRunCompleted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->RunTrigger();
}

void ACPP_PlayerController::OnLookTriggered(const FInputActionValue& Value)
{
	if (GetPawn() == nullptr) return;
	auto Rotations = Value.Get<FVector2D>();
	AddYawInput(Rotations.X);
	AddPitchInput(Rotations.Y);
}

void ACPP_PlayerController::OnCrouchStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
	{
		if (CPP_Character->bIsCrouched)
			CPP_Character->UnCrouch();
		else
			CPP_Character->Crouch();
	}
}

void ACPP_PlayerController::OnJumpStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		if(CPP_Character->bIsCrouched)
			CPP_Character->UnCrouch();
		else
			CPP_Character->Jump();
}

void ACPP_PlayerController::OnOpenInventoryStarted()
{
	UserCanvas->SetVisibility(ESlateVisibility::Hidden);
	UserInventory->SetVisibility(ESlateVisibility::Visible);
	//UserInventory->SetIsFocusable(true);

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	SetInputMode(FInputModeGameAndUI());
}

void ACPP_PlayerController::OnOpenInventoryCompleted()
{
	UserCanvas->SetVisibility(ESlateVisibility::Visible);
	UserInventory->SetVisibility(ESlateVisibility::Hidden);
	//UserInventory->SetIsFocusable(false);

	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
	SetInputMode(FInputModeGameOnly());
}

void ACPP_PlayerController::OnInteractionStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		if (auto* Item = Cast<ACPP_Item>(OutHitResult.GetActor()))
			if(!Item->GetHasOwner())
				CPP_Character->BeginItemInteraction(Item);
}

void ACPP_PlayerController::OnActionAStarted()
{
	if (auto* CPP_Character = Cast<ICPP_ActionInterface>(GetPawn()))
		CPP_Character->BeginActionAStarted();
}

void ACPP_PlayerController::OnActionATriggered()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->BeginActionATriggered();
}

void ACPP_PlayerController::OnActionACompleted()
{
	if (auto* CPP_Character = Cast<ICPP_ActionInterface>(GetPawn()))
		CPP_Character->BeginActionACompleted();
}

void ACPP_PlayerController::OnActionBStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->BeginActionBStarted();
}

void ACPP_PlayerController::OnActionBCompleted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->BeginActionBCompleted();
}

void ACPP_PlayerController::OnReloadTriggered()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->Reload();
}

void ACPP_PlayerController::OnMachinegunAutoStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->MachinegunAuto();
}

void ACPP_PlayerController::OnUseMedicalkitStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->UseMedicalkit();
}

void ACPP_PlayerController::OnWeaponAStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->BeginWeaponA();
}

void ACPP_PlayerController::OnWeaponBStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->BeginWeaponB();
}

void ACPP_PlayerController::OnWeaponCStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->BeginWeaponC();
}

void ACPP_PlayerController::OnWeaponDStarted()
{
	if (auto* CPP_Character = Cast<ACPP_Player>(GetPawn()))
		CPP_Character->BeginWeaponD();
}

void ACPP_PlayerController::ViewCenterRayTrace()
{
	if (GetPawn() == nullptr) return;
	FVector StartLocation = PlayerCameraManager.Get()->GetCameraLocation();
	FVector EndLocation = PlayerCameraManager.Get()->GetCameraRotation().Quaternion().GetForwardVector()
						  * InteractionTraceDistance + StartLocation;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetPawn());
	for (uint8 i = 0; i <= static_cast<int32>(ECharacterWeapon::Grenade); i++)
		if(auto* Weapon = Cast<ACPP_Player>(GetPawn())->GetWeapon(static_cast<ECharacterWeapon>(i)))
			IgnoreActors.Add(Weapon);

	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartLocation, EndLocation, 50, ObjectTypes,
		false, IgnoreActors, EDrawDebugTrace::None, OutHitResult, true);
}

void ACPP_PlayerController::ApplyRecoil()
{
	float Pitch = LeftRecoilPitch / 2;
	float Yaw = LeftRecoilYaw * RecoilDeltaTime;
	HandlingTime += RecoilDeltaTime;

	/*UE_LOG(TestKJH, Log, TEXT("Pitch : %f"), Pitch);
	UE_LOG(TestKJH, Log, TEXT("Yaw : %f"), Yaw);*/
	AddPitchInput(-Pitch);
	AddYawInput(Yaw);

	LeftRecoilPitch -= Pitch;
	LeftRecoilYaw -= Yaw;
	
	if (LeftRecoilPitch < 0.05 && LeftRecoilYaw < 0.05 && HandlingTime > 0.5)
	{
		GetWorld()->GetTimerManager().PauseTimer(RecoilHandle);
		LeftRecoilPitch = 0;
		LeftRecoilYaw = 0;
		HandlingTime = 0;
	}
}
