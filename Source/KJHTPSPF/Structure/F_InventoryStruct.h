#pragma once

#include "CoreMinimal.h"
#include "F_InventoryStruct.generated.h"

USTRUCT(BlueprintType)
struct FInventoryStruct
{
	GENERATED_BODY()

public:
	FInventoryStruct() : ItemID(""), Quantity(0), Weight(0), ItemClass(nullptr)
	{}

	bool operator==(const FInventoryStruct& Other) const
	{
		return (ItemID == Other.ItemID) && (Quantity == Other.Quantity) && (ItemClass == Other.ItemClass);		
	}

	UPROPERTY(VisibleAnywhere)
	FName ItemID;

	UPROPERTY(VisibleAnywhere)
	int Quantity;

	UPROPERTY(VisibleAnywhere)
	double Weight;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> ItemClass;
};