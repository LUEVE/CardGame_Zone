// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZPlayerController.generated.h"

/**
 * 
 */
class AZTable;
UCLASS()
class CARDGAME_ZONE_API AZPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Reliable, Client, BlueprintCallable)
	void ChangeRoundState();
	UFUNCTION(BlueprintImplementableEvent)
	void BPChangeRoundState();

	UFUNCTION(Reliable,BlueprintCallable, Client)
	void EndRound();
	UFUNCTION(BlueprintImplementableEvent)
	void BPEndRound();
	UFUNCTION(Server,Reliable,WithValidation)
	void ServeEndRound();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServeCreateDeck();

	UFUNCTION(BlueprintCallable)
	void DoServeEndRound();


	
	// do it in serve
	UFUNCTION()
	void InitEveryRound();

	void Init(int ID);
	
protected:
	void virtual BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void CreateRoundWidget();
private:
	void DestroyRoundWidget();
	

//variable
public:

	UPROPERTY(BlueprintReadWrite, Replicated, VisibleAnywhere)
	bool BisMyRound;
	// 0 or 1
	UPROPERTY(BlueprintReadWrite, Replicated)
	int PlayerControllerID;
protected:

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool BisCreateRoundWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MyRoundWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OpponentRoundWidget;
	UUserWidget* NowRoundWidget;
	UPROPERTY(BlueprintReadWrite)
	AZTable* CurrentTable;

	// The Num You Can Do Annexation or Expansion
	UPROPERTY(BlueprintReadWrite,Replicated)
	int OperateTime;

};
