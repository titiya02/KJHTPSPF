// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Item.h"
#include "KJHTPSPF.h"

// Sets default values
ACPP_Item::ACPP_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AssignDefaultSubobject(ItemCollision)->SetCollisionProfileName(TEXT("Item"));
}

void ACPP_Item::SetVisibilityType(bool bHasOwner)
{
	hasOwner = bHasOwner;
	if (hasOwner)
		ItemCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	else
		ItemCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void ACPP_Item::BeginActionBStarted()
{
}

void ACPP_Item::BeginActionBCompleted()
{
}

// Called when the game starts or when spawned
void ACPP_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FMontageData ACPP_Item::GetMontageData(ECharacterState state, int Value)
{
	if (OwnerMontageDataMap.Contains(state))
		if (*OwnerMontageDataMap.Find(state))
			return (*OwnerMontageDataMap.Find(state))->GetMontageData(Value);
	return FMontageData();
}

EItemType ACPP_Item::GetItemType()
{
	return ItemType;
}

int32 ACPP_Item::GetItemQuantity()
{
	return ItemQuantity;
}

double ACPP_Item::GetItemWeight()
{
	return ItemWeight;
}

void ACPP_Item::SetQuantity(int Value)
{
	ItemQuantity = Value;
}

void ACPP_Item::BeginActionAStarted()
{
}

void ACPP_Item::BeginActionACompleted()
{
}

