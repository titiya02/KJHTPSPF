#pragma once

#include "CoreMinimal.h"
#include "F_MontageData.generated.h"

USTRUCT(BlueprintType)
struct FMontageData
{
	GENERATED_BODY()

public:
	FMontageData() : Montage(nullptr), PlayRate(1.0), Section(TEXT("None"))
	{}

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly)
	double PlayRate;

	UPROPERTY(EditDefaultsOnly)
	FName Section;
};