// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "KJHTPSPF.h"

ACPP_GameModeBase::ACPP_GameModeBase()
{
	bUseSeamlessTravel = true;
	DefaultPawnClass = nullptr;
}

void ACPP_GameModeBase::StartPlay()
{
	Super::StartPlay();	
	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = 1;
	LatentAction.Linkage = 0;

	UGameplayStatics::LoadStreamLevel(GetWorld(), StartLevel, true, false, LatentAction);
	
}

void ACPP_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	FWorldDelegates::LevelAddedToWorld.AddUObject(this, &ThisClass::OnLevelLoaded);
}

void ACPP_GameModeBase::OnLevelLoaded(ULevel* Level, UWorld* World)
{
	if (!Level || !World) return;

	AActor* StartPoint = nullptr;

	for (AActor* Actor : Level->Actors)
	{
		if (Actor && Actor->IsA<APlayerStart>())
		{
			StartPoint = Actor;
			break;
		}
	}

	if (StartPoint)
		if (auto PlayerPawn = World->GetFirstPlayerController()->GetPawn())
			PlayerPawn->SetActorLocation(StartPoint->GetActorLocation());
	else
		UE_LOG(TestKJH, Log, TEXT("No StartPoint"));
}

void ACPP_GameModeBase::HandleSeamlessTravelPlayer(AController*& NewController)
{
	Super::HandleSeamlessTravelPlayer(NewController);
}