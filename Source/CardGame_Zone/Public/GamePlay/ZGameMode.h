// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ZGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CARDGAME_ZONE_API AZGameMode : public AGameMode
{
	GENERATED_BODY()

public:

protected:
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void AllPlayControllerHasPrepared();
	void RoundTick();
	

private:
	const int ReadyPlayerNum = 2;
	int NowPlayerNum;
	bool bHasPrepared;
	int ForPlayerControllerID;

	double BaseRoundTime;
};
