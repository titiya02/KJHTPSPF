// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structure/F_InventoryStruct.h"
#include "Enum/EItemType.h"
#include "CPP_Inventory.generated.h"

class ACPP_Item;

UCLASS()
class KJHTPSPF_API ACPP_Inventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Inventory();

	double GetCurrentVolume();
	double GetMaxVolume();
	bool AddItemToInventory(ACPP_Item* AddItem, FName AddItemID);
	UClass* TakeItemFromInventory(FName GetItemID, int& GetItemQuantity);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateInventoryUI(FString Name, int Num);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleInstanceOnly)
	double CurrentVolume = 0;

	UPROPERTY(EditDefaultsOnly)
	double MaxVolume = 300;

	UPROPERTY(EditInstanceOnly)
	TArray<FInventoryStruct> InventoryArray;
};
