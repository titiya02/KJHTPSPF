// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KJHTPSPF_API ACPP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	ACPP_GameModeBase();

protected:
	void StartPlay() override;

	void BeginPlay() override;

	void OnLevelLoaded(ULevel* Level, UWorld* World);

	void HandleSeamlessTravelPlayer(AController*& NewController) override;
protected:
	
	UPROPERTY(EditDefaultsOnly)
	FName StartLevel;
};
