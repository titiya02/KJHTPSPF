// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserInventory.generated.h"

class UCanvasPanel;
class UCPP_ItemListView;

UCLASS(Abstract)
class KJHTPSPF_API UCPP_UserInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateDroppedItem(FString Name, int Num);

	void UpdateInventoryItem(FString Name, int Num);

protected:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InventoryCanvas;

	UPROPERTY(meta = (BindWidget))
	UCPP_ItemListView* DroppedItems;

	UPROPERTY(meta = (BindWidget))
	UCPP_ItemListView* InventoryItems;
};
