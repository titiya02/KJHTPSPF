// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CPP_Player.h"
#include "Structure/F_InventoryStruct.h"

UCPP_GameInstance::UCPP_GameInstance()
{
}

void UCPP_GameInstance::Init()
{
	Super::Init();
}

void UCPP_GameInstance::LevelChange(FName LevelName)
{
	UGameplayStatics::OpenLevel(this, TEXT("TestInstance"));
}