
#include "CPP_SubLevelChanger.h"
#include "Components/BoxComponent.h"
#include "Character/CPP_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameMode.h"
#include "Components/WidgetComponent.h"
#include "Widget/CPP_LCText.h"
#include "KJHTPSPF.h"

ACPP_SubLevelChanger::ACPP_SubLevelChanger()
{
	SetRootComponent(AssignDefaultSubobject(Box));
	AssignDefaultSubobject(WidgetComponent)->SetupAttachment(RootComponent);
	WidgetComponent->SetCastShadow(false);
}

void ACPP_SubLevelChanger::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxBeginOverlap);
	if (auto Text = Cast<UCPP_LCText>(WidgetComponent->GetWidget()))
		Text->UpdateText(TEXT("To " + LevelLoad.ToString()));
}

void ACPP_SubLevelChanger::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Box->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnBoxBeginOverlap);
}

void ACPP_SubLevelChanger::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (auto Player = Cast<ACPP_Player>(OtherActor))
	{
		FLatentActionInfo LatentAction;
		LatentAction.CallbackTarget = this;
		LatentAction.UUID = 1;
		LatentAction.Linkage = 0;		

		UGameplayStatics::UnloadStreamLevel(GetWorld(), LevelUnload, LatentAction, false);

		LatentAction.UUID = 2;
		LatentAction.Linkage = 1;

		UGameplayStatics::LoadStreamLevel(GetWorld(), LevelLoad, true, false, LatentAction);
	}
}





