// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_CrossHair.generated.h"

class UImage; 

UCLASS()
class KJHTPSPF_API UCPP_CrossHair : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* CrossHair;
};
