// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ItemInfo.h"

void UCPP_ItemInfo::SetInfo(int Num, FString Name)
{
	if(Name == "")
		ItemInfo.ItemCounts = Num;
	else
	{
		ItemInfo.ItemName = Name;
		ItemInfo.ItemCounts = Num;
	}
}
