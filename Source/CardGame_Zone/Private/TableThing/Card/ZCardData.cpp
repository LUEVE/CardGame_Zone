// Fill out your copyright notice in the Description page of Project Settings.


#include "ZCardData.h"

// Sets default values
AZCardData::AZCardData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NetUpdateFrequency = 1;
}

// Called when the game starts or when spawned
void AZCardData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZCardData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

