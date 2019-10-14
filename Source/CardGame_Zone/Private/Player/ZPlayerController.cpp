// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ZPlayerController.h"
#include "UnrealNetwork.h"
#include "UserWidget.h"
#include "TimerManager.h"

void AZPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//@TODO judge widget whether null
}

void AZPlayerController::OnRep_CreateRoundWidget()
{

	UClass* TurnWidget = OpponentRoundWidget;
	if (BisMyRound)
		TurnWidget = MyRoundWidget;

	NowRoundWidget = CreateWidget<UUserWidget>(this, TurnWidget);
	if(NowRoundWidget)
	{
		NowRoundWidget->AddToViewport();
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle,this,&AZPlayerController::DestroyRoundWidget, 1, false, 3);
	}
	else
	{
		// @TODO log
	}

}


void AZPlayerController::DestroyRoundWidget()
{
	if(NowRoundWidget)
	{
		NowRoundWidget->RemoveFromParent();
		NowRoundWidget = nullptr;
	}

}

void AZPlayerController::ChangeRoundState_Implementation()
{

	OnRep_CreateRoundWidget();
}

void AZPlayerController::EndRound_Implementation()
{
	BPEndRound();
}

void AZPlayerController::Init(int ID)
{
	PlayerControllerID = ID;
	BisMyRound = false;
}

void AZPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZPlayerController, PlayerControllerID);
	DOREPLIFETIME(AZPlayerController, BisMyRound);
}

