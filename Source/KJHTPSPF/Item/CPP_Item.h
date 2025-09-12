// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Enum/EItemType.h"
#include "Enum/ECharacterState.h"
#include "CPP_MontageDataAsset.h"
#include "Interface/CPP_ActionInterface.h"
#include "CPP_Item.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Item : public AActor, public ICPP_ActionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Item();

	bool GetHasOwner() const { return hasOwner; };
	void SetVisibilityType(bool bHasOwner);
	int GetSizeofMontageMap() const { return OwnerMontageDataMap.Num(); };
	virtual void BeginActionBStarted();
	virtual void BeginActionBCompleted();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginActionAStarted() override;
	virtual void BeginActionACompleted() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FMontageData GetMontageData(ECharacterState state, int Value);
	EItemType GetItemType();
	int32 GetItemQuantity();
	double GetItemWeight();
	void SetQuantity(int Value);
protected:
	UPROPERTY(VisibleDefaultsOnly)
	UCapsuleComponent* ItemCollision;

	UPROPERTY(EditDefaultsOnly)
	EItemType ItemType = EItemType::Unknown;

	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterState, UCPP_MontageDataAsset*> OwnerMontageDataMap;

	UPROPERTY(EditDefaultsOnly)
	int ItemQuantity = 0;

	UPROPERTY(EditDefaultsOnly)
	double ItemWeight = 0;

	UPROPERTY(VisibleAnywhere)
	bool hasOwner = false;
};
