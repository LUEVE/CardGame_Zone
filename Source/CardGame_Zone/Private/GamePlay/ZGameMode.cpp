// Fill out your copyright notice in the Description page of Project Settings.


#include "ZGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ZZoneBlockGrid.h"
#include "Engine/World.h"
#include "ZPlayerController.h"
#include "TimerManager.h"
#include "ZGameState.h"

void AZGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	ForPlayerControllerID = -1;
	bHasPrepared = false;
	BaseRoundTime = 10;
	bDelayedStart = true;
}


void AZGameMode::RoundTick()
{
	// for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	// {
	// 	APlayerController* PC = It->Get();
	// 	if (PC)
	// 	{
	// 		AZPlayerController* ZPC = Cast<AZPlayerController>(PC);
	//
	// 		ZPC->EndRound();
	// 		ZPC->BisMyRound = !ZPC->BisMyRound;
	// 		//ZPC->ChangeRoundState();
	//
	// 	}
	// }

	auto GameState = GetGameState<AZGameState>();
	GameState->ChangeRound();
}

void AZGameMode::Tick(float DeltaSeconds)
{
	
	UE_LOG(LogTemp, Log, TEXT("Numplayers %d"),NumPlayers);
	//UE_LOG(LogTemp, Log, TEXT("Wether ReadyToStartMatch %d"), ReadyToStartMatch());
}



void AZGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	AllPlayControllerHasPrepared();
	
}

void AZGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();


	// FTimerHandle RoundTimerHandle;
	// GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AZGameMode::RoundTick, BaseRoundTime, true, 0);
}

void AZGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

}

void AZGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	

	if (NumPlayers >= 2)
	{
		ErrorMessage = "NumPlayer is two enough";
	}

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}


void AZGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	//auto nowPlayercontroller = NewPlayer;
	auto NowPlayerController = Cast<AZPlayerController>(NewPlayer);
	auto NowPlayerState = NewPlayer->PlayerState;
	ForPlayerControllerID++;
	NowPlayerController->Init(ForPlayerControllerID);
	UE_LOG(LogTemp, Log, TEXT("PostLogin now, Nowplayers %d"), NumPlayers);
	if (NumPlayers == 2 && !bHasPrepared)
	{
		StartMatch();
	}
}



void AZGameMode::AllPlayControllerHasPrepared()
{
	bHasPrepared = true;
	TArray<AActor*> ZoneBlockGrids;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZZoneBlockGrid::StaticClass(), ZoneBlockGrids);
	//GetAllActorsOfClass()
	auto ZoneBlockGird = Cast<AZZoneBlockGrid>(ZoneBlockGrids[0]);
	TArray<AActor*> PlayerControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZPlayerController::StaticClass(), PlayerControllers);
	ZoneBlockGird->InitPlayerBaseZone();

	// bool temp = false;
	// for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	// {
	// 	APlayerController* PC = It->Get();
	// 	if (PC)
	// 	{
	// 		AZPlayerController* ZPC = Cast<AZPlayerController>(PC);
	// 		ZPC->BisMyRound = temp;
	// 		temp = !temp;
	// 	}
	// }

	FTimerHandle RoundTimerHandle;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AZGameMode::RoundTick, BaseRoundTime, true, 3);
}




