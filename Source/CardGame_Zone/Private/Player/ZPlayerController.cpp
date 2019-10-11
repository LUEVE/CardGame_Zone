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

void AZPlayerController::CreateTurnWidget()
{

	UClass* TurnWidget = OpponentTurnWidget;
	if (BisMyRound)
		TurnWidget = MyTurnWidget;

	NowTurnWidget = CreateWidget<UUserWidget>(this, TurnWidget);
	if(NowTurnWidget)
	{
		NowTurnWidget->AddToViewport();
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle,this,&AZPlayerController::DestroyTurnWidget, 1, false, 1);
	}
	else
	{
		// @TODO log
	}

}

void AZPlayerController::DestroyTurnWidget()
{
	NowTurnWidget->RemoveFromParent();
	NowTurnWidget = nullptr;
}

void AZPlayerController::ChangeRoundState_Implementation()
{

	CreateTurnWidget();
}

void AZPlayerController::Init(int ID)
{
	PlayerControllerID = ID;
}

void AZPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZPlayerController, PlayerControllerID);
	DOREPLIFETIME(AZPlayerController, BisMyRound);
}

