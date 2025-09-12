// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LCText.h"
#include "Components/TextBlock.h"

void UCPP_LCText::UpdateText(FString Text)
{
	DoorText->SetText(FText::FromString(Text));
}
