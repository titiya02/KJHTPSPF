// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_LCText.generated.h"

class UTextBlock;

UCLASS(Abstract)
class KJHTPSPF_API UCPP_LCText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateText(FString Text);

protected:
	UPROPERTY(meta = (Bindwidget))
	UTextBlock* DoorText;
};
