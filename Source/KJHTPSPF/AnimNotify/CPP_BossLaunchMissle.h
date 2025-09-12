// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPP_BossLaunchMissle.generated.h"

/**
 * 
 */
UCLASS()
class KJHTPSPF_API UCPP_BossLaunchMissle : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Anim) override;	
};
