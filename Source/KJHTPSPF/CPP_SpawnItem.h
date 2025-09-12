// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_SpawnItem.generated.h"

class ACPP_Item;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_SpawnItem : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void SpawnItems();

	ULevel* GetCurrentSubLevel();

protected:
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<ACPP_Item> ItemClass;
};
