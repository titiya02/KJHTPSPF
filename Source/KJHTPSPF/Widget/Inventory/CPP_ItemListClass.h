// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CPP_ItemListClass.generated.h"

class UTextBlock;

UCLASS(Abstract)
class KJHTPSPF_API UCPP_ItemListClass : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UCPP_ItemListClass(const FObjectInitializer& ObjectInitializer);
	
protected:
	void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	FString CutOffString(FString Name);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemCounts;
};
