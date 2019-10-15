// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ZGameState.generated.h"

/**
 * 
 */
UCLASS()
class CARDGAME_ZONE_API AZGameState : public AGameState
{
	GENERATED_BODY()
public:
	void ChangeRound();
protected:
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;

	UFUNCTION(BlueprintCallable)
	void RoundHasChanged();
private:

// variable
protected:
	// 0 or 1,compare to ZPlayerController->PlayerControllerID
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=RoundHasChanged)
	int WhoRound;
};
