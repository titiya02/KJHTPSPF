// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Inventory.h"
#include "KJHTPSPF.h"
#include "Item/CPP_Item.h"
#include "Controller/CPP_PlayerController.h"

// Sets default values
ACPP_Inventory::ACPP_Inventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

double ACPP_Inventory::GetCurrentVolume()
{
	return CurrentVolume;
}

double ACPP_Inventory::GetMaxVolume()
{
	return MaxVolume;
}

bool ACPP_Inventory::AddItemToInventory(ACPP_Item* AddItem, FName AddItemID)
{
	double freeVolume = MaxVolume - CurrentVolume;
	int AddMaxQuantity = (int)(freeVolume / AddItem->GetItemWeight());
	if (AddMaxQuantity == 0) return false;

	for (FInventoryStruct& InventoryItem : InventoryArray)
	{
		if (AddItemID == InventoryItem.ItemID)
		{
			if (freeVolume < AddItem->GetItemQuantity() * AddItem->GetItemWeight())
			{
				InventoryItem.Quantity += AddMaxQuantity;
				CurrentVolume += AddMaxQuantity * AddItem->GetItemWeight();
				AddItem->SetQuantity(AddItem->GetItemQuantity() - AddMaxQuantity);
				UpdateInventoryUI(AddItemID.ToString(), AddMaxQuantity);
				return false;
			}
			else
			{
				InventoryItem.Quantity += AddItem->GetItemQuantity();
				CurrentVolume += AddItem->GetItemQuantity() * AddItem->GetItemWeight();
				UpdateInventoryUI(AddItemID.ToString(), AddItem->GetItemQuantity());
				return true;
			}
		}

	}
	FInventoryStruct AddArray;
	AddArray.ItemClass = AddItem->GetClass();
	AddArray.ItemID = AddItemID;
	AddArray.Weight = AddItem->GetItemWeight();
	if (freeVolume < AddItem->GetItemQuantity() * AddItem->GetItemWeight())
	{
		AddArray.Quantity = AddMaxQuantity;
		CurrentVolume += AddMaxQuantity * AddItem->GetItemWeight();
		AddItem->SetQuantity(AddItem->GetItemQuantity() - AddMaxQuantity);
		InventoryArray.Add(AddArray);
		UpdateInventoryUI(AddItemID.ToString(), AddMaxQuantity);
		return false;
	}
	else
	{
		AddArray.Quantity = AddItem->GetItemQuantity();
		CurrentVolume += AddItem->GetItemQuantity() * AddItem->GetItemWeight();
		InventoryArray.Add(AddArray);
		UpdateInventoryUI(AddItemID.ToString(), AddItem->GetItemQuantity());
		return true;
	}
	
}

UClass* ACPP_Inventory::TakeItemFromInventory(FName GetItemID, int& GetItemQuantity)
{
	UClass* ItemClass = nullptr;
	FInventoryStruct* DeleteValue = nullptr;
	for (FInventoryStruct& InventoryItem : InventoryArray)
	{
		if (GetItemID == InventoryItem.ItemID)
		{
			if (InventoryItem.Quantity <= GetItemQuantity)
			{
				GetItemQuantity = InventoryItem.Quantity;
				DeleteValue = &InventoryItem;
			}
			else
			{
				InventoryItem.Quantity -= GetItemQuantity;
			}
			CurrentVolume -= GetItemQuantity * InventoryItem.Weight;
			ItemClass = InventoryItem.ItemClass;
			break;
		}
	}
	if(ItemClass != nullptr)
		UpdateInventoryUI(GetItemID.ToString(), -GetItemQuantity);
	if (DeleteValue)
		InventoryArray.RemoveSingle(*DeleteValue);
	return ItemClass;
}

// Called when the game starts or when spawned
void ACPP_Inventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_Inventory::UpdateInventoryUI(FString Name, int Num)
{
	if (auto Controller = Cast<ACPP_PlayerController>(GetInstigatorController()))
		Controller->GetInventory()->UpdateInventoryItem(Name, Num);
}

// Called every frame
void ACPP_Inventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

