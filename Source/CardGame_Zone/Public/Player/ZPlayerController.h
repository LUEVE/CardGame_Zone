// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARDGAME_ZONE_API AZPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Reliable, Client, BlueprintCallable)
	void ChangeRoundState();

	UFUNCTION(Reliable,BlueprintCallable, Client)
	void EndRound();

	UFUNCTION(BlueprintImplementableEvent)
	void BPEndRound();

	void Init(int ID);
protected:
	void virtual BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void OnRep_CreateRoundWidget();
private:
	void DestroyRoundWidget();
	

//variable
public:

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_CreateRoundWidget, VisibleAnywhere)
	bool BisMyRound;
protected:
	UPROPERTY(BlueprintReadWrite,Replicated)
	int PlayerControllerID;
	UPROPERTY(BlueprintReadWrite, Replicated)
		bool BisCreateRoundWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MyRoundWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OpponentRoundWidget;
	UUserWidget* NowRoundWidget;
};
