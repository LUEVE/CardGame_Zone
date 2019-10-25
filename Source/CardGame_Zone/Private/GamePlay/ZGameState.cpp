// Fill out your copyright notice in the Description page of Project Settings.


#include "ZGameState.h"
#include "ZPlayerController.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "ZGameMode.h"
#include "TimerManager.h"
#include "ZTable.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "ZPlayerController.h"


void AZGameState::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	if(Role == ROLE_Authority)
	{
		auto GameMode = GetWorld()->GetAuthGameMode<AZGameMode>();
		RoundTime = GameMode->BaseRoundTime;

		CurrentTable = GetWorld()->SpawnActor<AZTable>(TableKind, FVector::ZeroVector, FRotator::ZeroRotator);
		CurrentTable->InitTable();
	
		
	}
	
}

void AZGameState::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	if (Role != ROLE_Authority)
	{
		if (CurrentTable)
		{
			// auto Place0 = CurrentTable->DeckPlace1->GetComponentLocation();
			// auto Place1 = CurrentTable->DeckPlace2->GetComponentLocation();
			// Player0_Deck = GetWorld()->SpawnActor<AZDeck>(DeckKind, Place0, FRotator::ZeroRotator);
			// if (Player0_Deck)
			// {
			// 	Player0_Deck->Init(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			// }
			// Player1_Deck = GetWorld()->SpawnActor<AZDeck>(DeckKind, Place1, FRotator::ZeroRotator);
			// if (Player1_Deck)
			// {
			// 	Player1_Deck->Init(UGameplayStatics::GetPlayerController(GetWorld(), 1));
			// }

			Cast<AZPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ServeCreateDeck();
		}
	}






}

void AZGameState::RoundHasChanged()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			AZPlayerController* ZPC = Cast<AZPlayerController>(PC);
			ZPC->ChangeRoundState();
		}
	}
}

void AZGameState::CreateDeckByController(AZPlayerController* PC)
{
	if (PC->PlayerControllerID)
	{
		FVector Place;
		Place = CurrentTable->DeckPlace1->GetComponentLocation();
		Player0_Deck = GetWorld()->SpawnActor<AZDeck>(DeckKind, Place, FRotator::ZeroRotator);
		if (Player0_Deck)
		{
			Player0_Deck->Init(PC);
		}
	}
	else
	{
		FVector Place;
		Place = CurrentTable->DeckPlace2->GetComponentLocation();
		Player1_Deck = GetWorld()->SpawnActor<AZDeck>(DeckKind, Place, FRotator::ZeroRotator);
		if (Player1_Deck)
		{
			Player1_Deck->Init(PC);
		}
	}
	
}

void AZGameState::ChangeRound()
{
	if (Role == ROLE_Authority)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Round);
		GetWorldTimerManager().SetTimer(TimerHandle_Round, this, &AZGameState::ChangeRound, RoundTime, false, RoundTime);
		WhoRound = WhoRound ? 0 : 1;
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
		{
			APlayerController* PC = It->Get();
			if (PC)
			{
				AZPlayerController* ZPC = Cast<AZPlayerController>(PC);
				ZPC->EndRound();
				if(ZPC->PlayerControllerID == WhoRound)
				{
					ZPC->BisMyRound = true;
				}
				else
				{
					ZPC->BisMyRound = false;
				}
			}
		}
	}

	//GetInstigatorController()
}

void AZGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZGameState,WhoRound);
	DOREPLIFETIME(AZGameState,RoundTime);
	DOREPLIFETIME(AZGameState, Player0_Deck);
	DOREPLIFETIME(AZGameState, Player1_Deck);
	// DOREPLIFETIME_CONDITION(AZGameState, Player0_Deck, COND_SkipOwner);
	// DOREPLIFETIME_CONDITION(AZGameState, Player1_Deck, COND_SkipOwner);
	DOREPLIFETIME(AZGameState,CurrentTable);
	//DOREPLIFETIME(AZPlayerController, BisMyRound);
}
