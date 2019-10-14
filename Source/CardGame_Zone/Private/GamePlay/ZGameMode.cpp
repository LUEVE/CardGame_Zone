// Fill out your copyright notice in the Description page of Project Settings.


#include "ZGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ZZoneBlockGrid.h"
#include "Engine/World.h"
#include "ZPlayerController.h"
#include "TimerManager.h"


void AZGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	ForPlayerControllerID = -1;
	NowPlayerNum = 0;
	bHasPrepared = false;
	BaseRoundTime = 10;

}


void AZGameMode::RoundTick()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			AZPlayerController* ZPC = Cast<AZPlayerController>(PC);

			ZPC->EndRound();
			ZPC->BisMyRound = !ZPC->BisMyRound;
			//ZPC->ChangeRoundState();

		}
	}
}

void AZGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	
}

void AZGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();


	// FTimerHandle RoundTimerHandle;
	// GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AZGameMode::RoundTick, BaseRoundTime, true, 0);
}


void AZGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	//auto nowPlayercontroller = NewPlayer;
	NowPlayerNum++;
	auto NowPlayerController = Cast<AZPlayerController>(NewPlayer);
	ForPlayerControllerID++;
	NowPlayerController->Init(ForPlayerControllerID);

	if (NowPlayerNum >= 2 && !bHasPrepared)
	{
		AllPlayControllerHasPrepared();
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

	bool temp = false;
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			AZPlayerController* ZPC = Cast<AZPlayerController>(PC);
			ZPC->BisMyRound = temp;
			temp = !temp;
		}
	}

	FTimerHandle RoundTimerHandle;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AZGameMode::RoundTick, BaseRoundTime, true, 3);
}




