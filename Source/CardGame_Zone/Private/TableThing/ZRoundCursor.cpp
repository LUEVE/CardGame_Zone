// Fill out your copyright notice in the Description page of Project Settings.


#include "ZRoundCursor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ZZoneBlockGrid.h"
// Sets default values
AZRoundCursor::AZRoundCursor()
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
void AZRoundCursor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZRoundCursor::Init()
{

}

// Called every frame
void AZRoundCursor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

