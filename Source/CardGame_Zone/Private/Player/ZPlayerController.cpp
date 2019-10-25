// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ZPlayerController.h"
#include "UnrealNetwork.h"
#include "UserWidget.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "ZGameState.h"
#include "ZTable.h"

void AZPlayerController::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AZTable> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		CurrentTable = *ActorItr;
		ClientMessage(ActorItr->GetName());
		ClientMessage(ActorItr->GetActorLocation().ToString());
	}

	//@TODO judge widget whether null
}

void AZPlayerController::CreateRoundWidget()
{

	UClass* TurnWidget = OpponentRoundWidget;
	if (BisMyRound)
		TurnWidget = MyRoundWidget;
	if(NowRoundWidget)
	{
		DestroyRoundWidget();
	}
	NowRoundWidget = CreateWidget<UUserWidget>(this, TurnWidget);
	if(NowRoundWidget)
	{
		NowRoundWidget->AddToViewport();
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle,this,&AZPlayerController::DestroyRoundWidget, 1, false, 2);
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
	CreateRoundWidget();
	BPChangeRoundState();
	CurrentTable->PlayTimeline();
}

void AZPlayerController::EndRound_Implementation()
{
	BPEndRound();
}

void AZPlayerController::ServeEndRound_Implementation()
{
	auto GS = GetWorld()->GetGameState<AZGameState>();
	if(GS)
		GS->ChangeRound();
 
}

bool AZPlayerController::ServeEndRound_Validate()
{

	return true;
}

void AZPlayerController::ServeCreateDeck_Implementation()
{
	auto GS = GetWorld()->GetGameState<AZGameState>();
	if (GS)
	{
		GS->CreateDeckByController(this);
	}
}

bool AZPlayerController::ServeCreateDeck_Validate()
{
	return true;
}

void AZPlayerController::DoServeEndRound()
{
	ServeEndRound();
}

void AZPlayerController::InitEveryRound()
{
	if (Role == ROLE_Authority)
	{
		OperateTime = 1;
		
	}
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
	DOREPLIFETIME(AZPlayerController, OperateTime);
}

