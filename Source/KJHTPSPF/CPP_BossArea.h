// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_BossArea.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_BossArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_BossArea();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBossAreaBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBossAreaBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BossAreaBox;

	UPROPERTY(EditInstanceOnly)
	APawn* Boss;
};
