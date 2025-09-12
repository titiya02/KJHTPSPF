#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_SubLevelChanger.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS(Abstract)
class KJHTPSPF_API ACPP_SubLevelChanger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_SubLevelChanger();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* Box;

	UPROPERTY(EditInstanceOnly)
	FName LevelLoad;

	UPROPERTY(EditInstanceOnly)
	FName LevelUnload;

	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* WidgetComponent;
};
