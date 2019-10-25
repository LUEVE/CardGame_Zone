// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/ZDeck.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ResourceManager.h"
#include "ConstructorHelpers.h"
#include "UnrealNetwork.h"
// Sets default values
AZDeck::AZDeck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	//PlayerOwner = -1;
	RootComponent = SceneComponent;
	BoxComponent->SetupAttachment(RootComponent);
	MeshComponent->SetupAttachment(RootComponent);

	BeginCardNum = 10;
	CardInterval = 1;
}

// Called when the game starts or when spawned
void AZDeck::BeginPlay()
{
	Super::BeginPlay();
	InitDeck();
}

void AZDeck::InitDeck()
{
	for (int i = 0; i < BeginCardNum; i++)
	{
		auto Location = BoxComponent->GetComponentLocation();
		FActorSpawnParameters SpawnParam;
		// 表示无视碰撞生成
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto card = GetWorld()->SpawnActor<AZCardBase>(DeckKind, Location + FVector(0,0,i*CardInterval), FRotator::ZeroRotator,SpawnParam);
		card->ChangeMaterial();
	//	card->SetActorEnableCollision(false);

		DeckCard.Add(card);
	}
}

// Called every frame
void AZDeck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZDeck::Init(AActor* PlayerOwner)
{
	SetOwner(PlayerOwner);
}


void AZDeck::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZDeck,DeckCard);
}


