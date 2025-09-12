// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ItemListView.h"
#include "Components/ListView.h"
#include "CPP_ItemInfo.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "KJHTPSPF.h"

void UCPP_ItemListView::UpdateListView(FString ItemName, int ItemNums)
{
	//UE_LOG(TestKJH, Log, TEXT("Test"));
	for (auto& CurrentItem : ItemList->GetListItems())
	{
		auto Item = Cast<UCPP_ItemInfo>(CurrentItem);
		if (Item->GetInfo().ItemName == ItemName)
		{
			if (Item->GetInfo().ItemCounts + ItemNums == 0)
				ItemList->RemoveItem(CurrentItem);
			else
				Item->SetInfo(Item->GetInfo().ItemCounts + ItemNums);

			ItemList->RegenerateAllEntries();
			return;
		}
	}

	UCPP_ItemInfo* Item = NewObject<UCPP_ItemInfo>();
	Item->SetInfo(ItemNums, ItemName);
	ItemList->AddItem(Item);

}
