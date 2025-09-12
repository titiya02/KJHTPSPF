// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_ItemListView.generated.h"

class UListView;

UCLASS(Abstract)
class KJHTPSPF_API UCPP_ItemListView : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateListView(FString ItemName, int ItemNums);

protected:
	UPROPERTY(meta=(BindWidget))
	UListView* ItemList;
};
