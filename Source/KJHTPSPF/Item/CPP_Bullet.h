// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Item.h"
#include "Enum/EBulletType.h"
#include "CPP_Bullet.generated.h"

UCLASS(Abstract)
class KJHTPSPF_API ACPP_Bullet : public ACPP_Item
{
	GENERATED_BODY()
	
public:
	ACPP_Bullet();

	EBulletType GetBulletType() const;
protected:
	void BeginActionAStarted() override;
	void BeginActionACompleted() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	EBulletType BulletType = EBulletType::Unknown;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
};
