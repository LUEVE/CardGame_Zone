// Fill out your copyright notice in the Description page of Project Settings.


#include "ZGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ZZoneBlockGrid.h"
#include "Engine/World.h"
#include "ZPlayerController.h"


void AZGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	ForPlayerControllerID = -1;
	NowPlayerNum = 0;
	bHasPrepared = false;
}

void AZGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	
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

}



