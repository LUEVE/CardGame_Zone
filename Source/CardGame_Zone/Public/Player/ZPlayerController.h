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
	void Init(int ID);
protected:
	void virtual BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void CreateTurnWidget();
private:
	void DestroyTurnWidget();
	

//variable
public:

	UPROPERTY(BlueprintReadWrite, Replicated, VisibleAnywhere)
	bool BisMyRound;
protected:
	UPROPERTY(BlueprintReadWrite,Replicated)
	int PlayerControllerID;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MyTurnWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OpponentTurnWidget;
	UUserWidget* NowTurnWidget;
};
