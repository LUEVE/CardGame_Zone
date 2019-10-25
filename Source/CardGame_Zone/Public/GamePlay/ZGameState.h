// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include <queue>
#include <functional>
#include "ZDeck.h"
#include "ZGameState.generated.h"

/**
 * 
 */

//class FTimerHandle;
//class AZDeck;
class AZTable;
UCLASS()
class CARDGAME_ZONE_API AZGameState : public AGameState
{
	GENERATED_BODY()
public:
	friend class AZPlayerController;
	//void DoServeChangeRound();
	void ChangeRound();
protected:
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	
	UFUNCTION(BlueprintCallable)
	void RoundHasChanged();
private:

// variable
public:
	UPROPERTY(BlueprintReadWrite, Replicated)
	int RoundTime;
	UPROPERTY(Replicated)
	AZTable* CurrentTable;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AZDeck> DeckKind;
	UPROPERTY(BlueprintReadWrite,Replicated)
	AZDeck* Player0_Deck;
	UPROPERTY(BlueprintReadWrite,Replicated)
	AZDeck* Player1_Deck;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AZTable> TableKind;
	
protected:
	// 0 or 1,compare to ZPlayerController->PlayerControllerID
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=RoundHasChanged)
	int WhoRound;

	FTimerHandle TimerHandle_Round;


	//@TODO queue Function for end round and begin round to Settle Card effect.
	std::queue<std::function<void()>> CardEffectQueue;
private:
	void CreateDeckByController(AZPlayerController* PC);



};
