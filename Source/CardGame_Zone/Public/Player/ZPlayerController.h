// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARDGAME_ZONE_API AZPlayerController : public APlayerController
{
	GENERATED_BODY()


//variable
public:
	void Init(int ID);
protected:
	UPROPERTY(BlueprintReadWrite,Replicated)
	int PlayerControllerID;
	
};
