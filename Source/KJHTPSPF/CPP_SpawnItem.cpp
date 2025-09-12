

#include "CPP_SpawnItem.h"
#include "Item/CPP_Item.h"
#include "KJHTPSPF.h"


void ACPP_SpawnItem::BeginPlay()
{
	Super::BeginPlay();
	SpawnItems();
	Destroy();
	
}

void ACPP_SpawnItem::SpawnItems()
{
	if (ItemClass == nullptr) return;

	FHitResult Result;
	FVector Start = GetActorLocation();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(
		Result,
		Start + FVector(0, 0, 500),
		Start - FVector(0, 0, 500),
		ECollisionChannel::ECC_Visibility,
		Params
	);

	FActorSpawnParameters SpawnParams;
	SpawnParams.OverrideLevel = GetCurrentSubLevel();

	FVector SpawnLocation = Result.Location;
	SpawnLocation.Z += 5;

	GetWorld()->SpawnActor<AActor>(ItemClass, SpawnLocation, FRotator(), SpawnParams);
}

ULevel* ACPP_SpawnItem::GetCurrentSubLevel()
{
	for (ULevelStreaming* StreamingLevel : GetWorld()->GetStreamingLevels())
	{
		if (StreamingLevel->IsLevelLoaded())
		{
			ULevel* LoadedLevel = StreamingLevel->GetLoadedLevel();
			if (LoadedLevel != GetWorld()->PersistentLevel)
				return LoadedLevel;
		}
	}

	return nullptr;
}


