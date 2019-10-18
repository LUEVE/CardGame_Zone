// Fill out your copyright notice in the Description page of Project Settings.


#include "ZGameState.h"
#include "ZPlayerController.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "ZGameMode.h"
#include "TimerManager.h"


void AZGameState::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	if(Role == ROLE_Authority)
	{
		auto GameMode = GetWorld()->GetAuthGameMode<AZGameMode>();
		RoundTime = GameMode->BaseRoundTime;
	}
	
}

void AZGameState::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
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
	//DOREPLIFETIME(AZPlayerController, BisMyRound);
}
