// Fill out your copyright notice in the Description page of Project Settings.


#include "ZCardBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
AZCardBase::AZCardBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CardBackComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardBackComp"));
	CardFaceComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardFaceComp"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	//PlayerOwner = -1;
	RootComponent = SceneComponent;
	BoxComponent->SetupAttachment(RootComponent);

	CardFaceComponent->SetupAttachment(RootComponent);
	CardBackComponent->SetupAttachment(CardFaceComponent);
	Speed = 1;
}

// Called when the game starts or when spawned
void AZCardBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZCardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZCardBase::ChangeMaterial()
{
	CardBackComponent->SetMaterial(0, CardMaterial);
}

