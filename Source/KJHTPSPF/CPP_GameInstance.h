// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPP_GameInstance.generated.h"

UCLASS()
class KJHTPSPF_API UCPP_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	UCPP_GameInstance();

public:
	
	void LevelChange(FName LevelName);
protected:
	virtual void Init() override;

protected:
	
};
