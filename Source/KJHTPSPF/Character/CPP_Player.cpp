// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player.h"
#include "KJHTPSPF.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Controller/CPP_PlayerController.h"
#include "Widget/CPP_UserCanvas.h"
#include "Item/Weapon/CPP_Shotgun.h"
#include "Item/Weapon/CPP_Machinegun.h"
#include "Item/CPP_Bullet.h"
#include "CPP_Inventory.h"
#include "Item/Weapon/CPP_Grenade.h"
#include "Curves/CurveVector.h"
#include "Components/PostProcessComponent.h"
#include "Kismet/KismetMaterialLibrary.h"

ACPP_Player::ACPP_Player()
{
	SetGenericTeamId(FGenericTeamId(1));

	AssignDefaultSubobject(SpringArm)->SetupAttachment(GetCapsuleComponent());
	AssignDefaultSubobject(PostProcess)->SetupAttachment(GetCapsuleComponent());
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 50;

	AssignDefaultSubobject(Camera)->SetupAttachment(SpringArm);

	if (!FAGunMeshs.Contains(ECharacterWeapon::Machinegun))
	{
		FAGunMeshs.Add(ECharacterWeapon::Machinegun) = CreateDefaultSubobject<USkeletalMeshComponent>("FAMachineGun");
		auto FAGunMesh = *FAGunMeshs.Find(ECharacterWeapon::Machinegun);
		FAGunMesh->SetupAttachment(Camera);
		FAGunMesh->bHiddenInGame = true;
		FAGunMesh->bOnlyOwnerSee = true;
	}
	if (!FAGunMeshs.Contains(ECharacterWeapon::Shotgun))
	{
		FAGunMeshs.Add(ECharacterWeapon::Shotgun) = CreateDefaultSubobject<USkeletalMeshComponent>("FAShotGun");
		auto FAGunMesh = *FAGunMeshs.Find(ECharacterWeapon::Shotgun);
		FAGunMesh->SetupAttachment(Camera);
		FAGunMesh->bHiddenInGame = true;
		FAGunMesh->bOnlyOwnerSee = true;
	}
}

void ACPP_Player::SetController(AController* OnwerController)
{

	if (auto APlayerController = Cast<ACPP_PlayerController>(OnwerController))
	{
		PlayerController = APlayerController;
		PlayerController->GetCanvas()->UpdateHealthBar(CurrentHealthPercent());
	}
}

TArray<ACPP_BaseWeapon*> ACPP_Player::GetAllWeapons() const
{
	TArray<ACPP_BaseWeapon*> AllWeapons;

	for (auto& Weapon : CurrentArmedWeapons)
		AllWeapons.Add(Weapon.Value);

	return AllWeapons;
}

ACPP_Inventory* ACPP_Player::GetInventory() const
{
	return Inventory;
}

void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(TestKJH, Log, TEXT("Player : %d"), TeamId.GetId());

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	Inventory = GetWorld()->SpawnActor<ACPP_Inventory>(SpawnParameters);
	if (Inventory)
	{
		Inventory->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Inventory->Rename(nullptr, GetWorld()->PersistentLevel);
	}

	// TimeLine
	if (TimeLineFOV && TimeLineTargetArmFirst && TimeLineTargetArmThird &&
		TimeLineOffsetFirst && TimeLineOffsetThird && CurveFlash)
	{
		FOnTimelineFloat FloatTimeLineProgressFirst;
		FOnTimelineFloat FloatTimeLineProgressThird;
		FOnTimelineFloat FloatTimeLineProgressFlash;

		FloatTimeLineProgressFirst.BindUFunction(this, FName("TimeLineFirstUpdate"));
		FloatTimeLineProgressThird.BindUFunction(this, FName("TimeLineThirdUpdate"));
		FloatTimeLineProgressFlash.BindUFunction(this, FName("FlashTimeLineBang"));

		ZoomTimeLineFirst.AddInterpFloat(TimeLineTargetArmFirst, FloatTimeLineProgressFirst);
		ZoomTimeLineThird.AddInterpFloat(TimeLineTargetArmThird, FloatTimeLineProgressThird);
		FlashTimeLine.AddInterpFloat(CurveFlash, FloatTimeLineProgressFlash);
		
		ZoomTimeLineFirst.SetLooping(false);
		ZoomTimeLineThird.SetLooping(false);
		FlashTimeLine.SetLooping(false);
	}
}

void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	ZoomTimeLineFirst.TickTimeline(DeltaTime);
	ZoomTimeLineThird.TickTimeline(DeltaTime);
	FlashTimeLine.TickTimeline(DeltaTime);

	if (bIsWalkingFront && bIsRun)
		GetCharacterMovement()->MaxWalkSpeed = 600;
	else
		GetCharacterMovement()->MaxWalkSpeed = 300;
}

float ACPP_Player::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(PlayerController)
		PlayerController->GetCanvas()->UpdateHealthBar(CurrentHealthPercent());
	return DamageAmount;
}

void ACPP_Player::ArmingWeapon(ECharacterWeapon Type)
{
	Super::ArmingWeapon(Type);
	if(*CurrentArmedWeapons.Find(Type) != nullptr &&
	   (Type == ECharacterWeapon::Machinegun ||
	   Type == ECharacterWeapon::Shotgun))
		PlayerController->GetCanvas()->UpdateCrossHairVisible(true);
}

void ACPP_Player::DisArmingWeapon()
{
	Super::DisArmingWeapon();
	PlayerController->GetCanvas()->UpdateCrossHairVisible(false);
}

void ACPP_Player::TimeLineFirstUpdate(float DeltaTime)
{
	double Time = ZoomTimeLineFirst.GetPlaybackPosition();
	
	double CurrentFOV = TimeLineFOV->GetFloatValue(Time);
	double CurrentTargetArmF = TimeLineTargetArmFirst->GetFloatValue(Time);
	FVector CurrentOffsetF = TimeLineOffsetFirst->GetVectorValue(Time);
	
	Camera->FieldOfView = CurrentFOV;
	SpringArm->TargetArmLength = CurrentTargetArmF;
	SpringArm->SocketOffset = CurrentOffsetF;
}

void ACPP_Player::TimeLineThirdUpdate(float DeltaTime)
{
	double Time = ZoomTimeLineThird.GetPlaybackPosition();
	
	double CurrentFOV = TimeLineFOV->GetFloatValue(Time);
	double CurrentTargetArmT = TimeLineTargetArmThird->GetFloatValue(Time);
	FVector CurrentOffsetT = TimeLineOffsetThird->GetVectorValue(Time);

	Camera->FieldOfView = CurrentFOV;
	SpringArm->TargetArmLength = CurrentTargetArmT;
	SpringArm->SocketOffset = CurrentOffsetT;
}

void ACPP_Player::FlashTimeLineBang(float DeltaTime)
{
	double Time = FlashTimeLine.GetPlaybackPosition();
	double CurrentWeight = CurveFlash->GetFloatValue(Time);

	//UE_LOG(TestKJH, Log, TEXT("%f"), CurrentWeight);

	UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MPC_FlashBang, TEXT("weight"), CurrentWeight);
}

void ACPP_Player::RunTrigger()
{
	if (!bIsAiming)
	{
		if (!bIsRun)
			bIsRun = true;
		else
			bIsRun = false;
	}
}

void ACPP_Player::BeginWeaponA()
{
	Super::BeginWeaponA();
	OffAiming();
}

void ACPP_Player::BeginWeaponB()
{
	Super::BeginWeaponB();
	OffAiming();
}

void ACPP_Player::BeginWeaponC()
{
	Super::BeginWeaponC();
	OffAiming();
}

void ACPP_Player::BeginWeaponD()
{
	Super::BeginWeaponD();
	OffAiming();
}

void ACPP_Player::BeginActionBStarted()
{
	if (ArmedWeapon != nullptr &&
		CharacterState != ECharacterState::Reloading &&
		CharacterState != ECharacterState::Acting &&
		CharacterState != ECharacterState::Arming &&
		CharacterState != ECharacterState::Died)
	{
		bIsRun = false;
		ArmedWeapon->BeginActionBStarted();
	}
	
}

void ACPP_Player::BeginActionBCompleted()
{
	if (ArmedWeapon != nullptr &&
		CharacterState != ECharacterState::Reloading &&
		CharacterState != ECharacterState::Acting &&
		CharacterState != ECharacterState::Arming &&
		CharacterState != ECharacterState::Died)
		ArmedWeapon->BeginActionBCompleted();
}

void ACPP_Player::OnAiming(int intPerson)
{
	CurrentAiming = intPerson;	
	switch (CurrentAiming)
	{
	case 1:
		if (FAGunMeshs.Contains(WeaponType))
			if (auto FAMesh = *FAGunMeshs.Find(WeaponType))
				FAMesh->SetHiddenInGame(false);	
		if (IsLocallyControlled())
		{
			HideBoneAndChildren("head");
			HideBoneAndChildren("lowerarm_l");
			HideBoneAndChildren("lowerarm_r");
			ArmedWeapon->SetActorHiddenInGame(true);
		}
		SpringArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("head"));
		SpringArm->SetWorldRotation(FRotator(0,90,0));
		ZoomTimeLineFirst.Play();
		break;
	case 3:
		ZoomTimeLineThird.Play();
		break;
	}
	bIsAiming = true;
}

void ACPP_Player::OffAiming()
{
	switch (CurrentAiming)
	{
	case 1:
		if (FAGunMeshs.Contains(WeaponType))
			if (auto FAMesh = *FAGunMeshs.Find(WeaponType))
				FAMesh->SetHiddenInGame(true);
		if (IsLocallyControlled())
		{
			UnHideBoneAndChildren("head");
			UnHideBoneAndChildren("lowerarm_l");
			UnHideBoneAndChildren("lowerarm_r");
			ArmedWeapon->SetActorHiddenInGame(false);
		}
		SpringArm->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		SpringArm->SetWorldRotation(FRotator(0, 0, 0));
		ZoomTimeLineFirst.Reverse();
		break;
	case 3:
		ZoomTimeLineThird.Reverse();
		break;
	}
	CurrentAiming = 0;
	
	bIsAiming = false;
}

void ACPP_Player::BeginItemInteraction(ACPP_Item* InteractionActor)
{
	if (CharacterState != ECharacterState::Died &&
		CharacterState != ECharacterState::Arming &&
		CharacterState != ECharacterState::Acting &&
		CharacterState != ECharacterState::Reloading)
	{
		if (auto* Weapon = Cast<ACPP_BaseWeapon>(InteractionActor))
		{
			if (CurrentArmedWeapons.Contains(Weapon->GetWeaponType()))
			{
				if (!(*CurrentArmedWeapons.Find(Weapon->GetWeaponType())))
				{
					if (MontageDataMap.Contains(ECharacterState::Acting))
						if (MontageDataMap.Find(ECharacterState::Acting))
						{
							CharacterState = ECharacterState::Acting;
							FMontageData MontageData = (*MontageDataMap.Find(ECharacterState::Acting))->GetMontageData(0);
							PlayAnimMontageData(MontageData);
							CurrentArmedWeapons.Add(Weapon->GetWeaponType(), Weapon);
							Weapon->SetOwner(this);
							Weapon->SetInstigator(this);
							Weapon->SetVisibilityType(true);
							Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Weapon->GetSocketOnUnarmed());
							Weapon->Rename(nullptr, GetWorld()->PersistentLevel);
						}
				}
				else if (*CurrentArmedWeapons.Find(ECharacterWeapon::Grenade))
				{
					if (MontageDataMap.Contains(ECharacterState::Acting))
						if (MontageDataMap.Find(ECharacterState::Acting))
						{
							CharacterState = ECharacterState::Acting;
							FMontageData MontageData = (*MontageDataMap.Find(ECharacterState::Acting))->GetMontageData(0);
							PlayAnimMontageData(MontageData);
							if (Inventory->AddItemToInventory(Weapon, EnumToFName(Weapon->GetWeaponType())))
								Weapon->Destroy();
						}
				}
			}
		}
		else
		{
			if (MontageDataMap.Contains(ECharacterState::Acting))
				if (MontageDataMap.Find(ECharacterState::Acting))
				{
					CharacterState = ECharacterState::Acting;
					FMontageData MontageData = (*MontageDataMap.Find(ECharacterState::Acting))->GetMontageData(0);
					PlayAnimMontageData(MontageData);
					if (auto* Bullet = Cast<ACPP_Bullet>(InteractionActor))
					{
						if (Inventory->AddItemToInventory(Bullet, EnumToFName(Bullet->GetBulletType())))
							Bullet->Destroy();
					}
					else
					{
						Inventory->AddItemToInventory(InteractionActor, EnumToFName(InteractionActor->GetItemType()));
						InteractionActor->Destroy();
					}
					InteractionActor->SetActorLocation(GetActorLocation());
				}
		}
	}
}

void ACPP_Player::Reload()
{
	if (CharacterState != ECharacterState::Reloading &&
		CharacterState != ECharacterState::Arming &&
		CharacterState != ECharacterState::Acting &&
		CharacterState != ECharacterState::Died)
	{
		if (WeaponType != ECharacterWeapon::Unknown && 
			WeaponType != ECharacterWeapon::Grenade &&
			WeaponType != ECharacterWeapon::Melee)
		{
			if (auto* Gun = Cast<ACPP_Basegun>(ArmedWeapon))
			{
				if (Gun->NeedBullet() == 0) return;
				if (CurrentAiming != 0)
					OffAiming();

				else if (Gun->NeedBullet() > 0)
				{
					NeedBulletQuantity = Gun->NeedBullet();
					if (Inventory->TakeItemFromInventory(EnumToFName(Gun->GetBulletType()), NeedBulletQuantity))
					{
						
						if (NeedBulletQuantity == 0) return;
						NeedBulletQuantity += Gun->GetCurrentBullet();
						FMontageData MontageData = ArmedWeapon->GetMontageData(ECharacterState::Acting, 1);
						PlayAnimMontageData(MontageData);
						Gun->PlayWeaponMontage(1);
						CharacterState = ECharacterState::Reloading;
					}
				}
			}
		}
	}
}

void ACPP_Player::ReloadBullet(int Quantity)
{
	Super::ReloadBullet(Quantity);
	ArmedWeapon->UpdateWeaponUI();
}

void ACPP_Player::MachinegunAuto()
{
	if (ArmedWeapon != nullptr &&
		CharacterState != ECharacterState::Arming &&
		CharacterState != ECharacterState::Died)
	{
		if (auto Machinegun = Cast<ACPP_Machinegun>(ArmedWeapon))
			Machinegun->SetIsAuto();
	}
}

void ACPP_Player::UseMedicalkit()
{
	if (CharacterState != ECharacterState::Arming &&
		CharacterState != ECharacterState::Acting &&
		CharacterState != ECharacterState::Reloading &&
		CharacterState != ECharacterState::Died)
	{
		int TakeOne = 1;
		if (Inventory->TakeItemFromInventory(EnumToFName(EItemType::MedicalKit), TakeOne) != nullptr)
		{
			CharacterState = ECharacterState::Acting;
			FMontageData MontageData = (*MontageDataMap.Find(ECharacterState::Acting))->GetMontageData(1);
			PlayAnimMontageData(MontageData);
		}
	}
}

void ACPP_Player::GainHealth()
{
	LifeNow += 50;
	if (LifeNow > LifeMax)
		LifeNow = LifeMax;

	PlayerController->GetCanvas()->UpdateHealthBar(CurrentHealthPercent());
}

void ACPP_Player::BeginActionAStarted()
{
	if (ArmedWeapon &&
		CharacterState != ECharacterState::Reloading &&
		CharacterState != ECharacterState::Acting &&
		CharacterState != ECharacterState::Arming &&
		CharacterState != ECharacterState::Died)
	{
		Super::BeginActionAStarted();
		if (auto Grenade = Cast<ACPP_Grenade>(ArmedWeapon))
		{
			FMontageData MontageData = ArmedWeapon->GetMontageData(ECharacterState::Acting, 0);
			PlayAnimMontageData(MontageData);
		}
		if(CurrentAiming == 1)
			if(auto Gun = Cast<ACPP_Basegun>(ArmedWeapon))
				if(Gun->GetCurrentBullet() != 0)
					PlayFAMeshMontage();
	}
}

void ACPP_Player::BeginActionACompleted()
{
	Super::BeginActionACompleted();
}

void ACPP_Player::PlayFAMeshMontage()
{
	if (auto Gun = Cast<ACPP_Basegun>(ArmedWeapon))
		Gun->GetSkeletalMesh()->GetAnimInstance()->Montage_Play(FAGunMontages[Gun->GetWeaponType()]);
}

void ACPP_Player::HideBoneAndChildren(FName ParentBoneName)
{
	const int ParentBoneIndex = GetMesh()->GetBoneIndex(ParentBoneName);
	if (ParentBoneIndex == INDEX_NONE) return;

	GetMesh()->HideBoneByName(ParentBoneName, EPhysBodyOp::PBO_None);

	const int NumBones = GetMesh()->GetNumBones();
	for (int BoneIndex = 0; BoneIndex < NumBones; BoneIndex++)
	{
		if (GetMesh()->GetSkeletalMeshAsset()->GetRefSkeleton().GetParentIndex(BoneIndex) == ParentBoneIndex)
		{
			HideBoneAndChildren(GetMesh()->GetBoneName(BoneIndex));
		}
	}
}

void ACPP_Player::UnHideBoneAndChildren(FName ParentBoneName)
{
	const int ParentBoneIndex = GetMesh()->GetBoneIndex(ParentBoneName);
	if (ParentBoneIndex == INDEX_NONE) return;

	GetMesh()->UnHideBoneByName(ParentBoneName);

	const int NumBones = GetMesh()->GetNumBones();
	for (int BoneIndex = 0; BoneIndex < NumBones; BoneIndex++)
	{
		if (GetMesh()->GetSkeletalMeshAsset()->GetRefSkeleton().GetParentIndex(BoneIndex) == ParentBoneIndex)
		{
			UnHideBoneAndChildren(GetMesh()->GetBoneName(BoneIndex));
		}
	}
}

void ACPP_Player::ChangeWeapon()
{
	if (bChangeWeapon)
	{
		bChangeWeapon = false;
		ArmingWeapon(ChangeWeaponType);
		ChangeWeaponType = ECharacterWeapon::Unknown;
	}
}

void ACPP_Player::ThrowGrenade()
{
	Super::ThrowGrenade();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = this;
	SpawnParameters.Owner = this;

	int GetGrenade = 1;
	auto Grenade = Cast<ACPP_Grenade>(
		GetWorld()->SpawnActor<AActor>
		(
			ArmedWeapon->GetClass(),
			GetActorLocation() + GetActorForwardVector() * 50,
			GetActorForwardVector().Rotation(),
			SpawnParameters
		)
	);
	Grenade->StartedThrow();
	if (Inventory->TakeItemFromInventory(EnumToFName(ArmedWeapon->GetWeaponType()), GetGrenade) == nullptr)
	{
		CurrentArmedWeapons[ArmedWeapon->GetWeaponType()] = nullptr;
		WeaponType = ECharacterWeapon::Unknown;
		ArmedWeapon->Destroy();
		ArmedWeapon = nullptr;
	}
}

void ACPP_Player::HitFlashBang(double Time)
{
	UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MPC_FlashBang, TEXT("weight"), 1);

	GetWorld()->GetTimerManager().SetTimer(FlashBangTimer, this, &ThisClass::PlayFlashBangTimer, 1, false, Time);
}

void ACPP_Player::PlayFlashBangTimer()
{
	FlashTimeLine.PlayFromStart();
}
