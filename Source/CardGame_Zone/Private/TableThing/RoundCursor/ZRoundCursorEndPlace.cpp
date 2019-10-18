// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundCursor/ZRoundCursorEndPlace.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AZRoundCursorEndPlace::AZRoundCursorEndPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	//PlayerOwner = -1;
	RootComponent = SceneComponent;
	BoxComponent->SetupAttachment(RootComponent);
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AZRoundCursorEndPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZRoundCursorEndPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

