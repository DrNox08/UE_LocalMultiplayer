// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoopGameMode.generated.h"

class AWinTriggerBox;
/**
 * 
 */
UCLASS()
class DEMO_MULTIPLAYER_API ACoopGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void RegisterWinTrigger(AWinTriggerBox* Trigger);
	void OnTriggerStateChanged();

private:
	
	TArray<AWinTriggerBox*> WinTriggers;

	bool bGameWon = false;
};
