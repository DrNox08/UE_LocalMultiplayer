// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Game/CoopGameMode.h"

#include "Demo_MultiplayerPlayerController.h"
#include "Public/Game/WinTriggerBox.h"

void ACoopGameMode::RegisterWinTrigger(AWinTriggerBox* Trigger)
{
	WinTriggers.AddUnique(Trigger);
}

void ACoopGameMode::OnTriggerStateChanged()
{
	if (bGameWon) return;
	
	UE_LOG(LogTemp, Warning, TEXT("OnTriggerStateChanged - Triggers: %d"), WinTriggers.Num());

	for (AWinTriggerBox* Trigger : WinTriggers)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger %s occupied: %s"), *GetNameSafe(Trigger), Trigger->IsOccupied() ? TEXT("YES") : TEXT("NO"));
		if (!Trigger || !Trigger->IsOccupied())
		{
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ALL TRIGGERS OCCUPIED - YOU WON!"));
	bGameWon = true;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (ADemo_MultiplayerPlayerController* PC = Cast<ADemo_MultiplayerPlayerController>(It->Get()))
		{
			PC->Client_ShowWinScreen();
		}
	}
}