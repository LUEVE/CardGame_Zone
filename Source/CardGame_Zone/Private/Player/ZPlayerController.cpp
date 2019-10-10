// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ZPlayerController.h"
#include "UnrealNetwork.h"

void AZPlayerController::Init(int ID)
{
	PlayerControllerID = ID;
}

void AZPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZPlayerController, PlayerControllerID);
}

