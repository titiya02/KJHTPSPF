// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ItemListClass.h"
#include "Components/TextBlock.h"
#include "CPP_ItemInfo.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "KJHTPSPF.h"

UCPP_ItemListClass::UCPP_ItemListClass(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	this->SetIsFocusable(true);
}

void UCPP_ItemListClass::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (auto ItemObject = Cast<UCPP_ItemInfo>(ListItemObject))
	{
		ItemName->SetText(FText::FromString(CutOffString(ItemObject->GetInfo().ItemName)));
		ItemCounts->SetText(FText::FromString(FString::FromInt(ItemObject->GetInfo().ItemCounts)));
	}
}

FString UCPP_ItemListClass::CutOffString(FString Name)
{
	FString ReturnString;
	FString a;
	Name.Split(TEXT("::"), &a, &ReturnString);
	return ReturnString;
}
