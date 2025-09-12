// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_UserInventory.h"
#include "Inventory/CPP_ItemListView.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "KJHTPSPF.h"

void UCPP_UserInventory::UpdateDroppedItem(FString Name, int Num)
{
	DroppedItems->UpdateListView(Name, Num);
}

void UCPP_UserInventory::UpdateInventoryItem(FString Name, int Num)
{
	InventoryItems->UpdateListView(Name, Num);
}