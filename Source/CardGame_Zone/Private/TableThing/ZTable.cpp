// Fill out your copyright notice in the Description page of Project Settings.


#include "ZTable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ZZoneBlockGrid.h"
#include "UnrealNetwork.h"
#include "ZRoundCursor.h"
#include "ConstructorHelpers.h"
#include "ZGameState.h"

// Sets default values
AZTable::AZTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComp"));
	DeckPlace1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeckComp1"));
	DeckPlace2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeckComp2"));


	RootComponent = SceneComponent;
	BoxComponent->SetupAttachment(SceneComponent);
	MeshComponent->SetupAttachment(SceneComponent);
	DeckPlace1->SetupAttachment(SceneComponent);
	DeckPlace2->SetupAttachment(SceneComponent);
	SetReplicates(true);

	CursorBeginLocation = FVector(0, 0, 0);
	CursorEndLocation = FVector(0, 0, 0);
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/CardGamePlace/Table/RoundCursorCurve"));
	check(Curve.Succeeded());
	FloatCurve = Curve.Object;
}

// Called when the game starts or when spawned
void AZTable::BeginPlay()
{


	Super::BeginPlay();

	InitRoundCursor();

}

void AZTable::InitTable()
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentZoneBlockGrid = GetWorld()->SpawnActor<AZZoneBlockGrid>(ZoneBlockGrid, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);
	if (CurrentZoneBlockGrid)
	{
		CurrentZoneBlockGrid->SetOwner(this);
		CurrentZoneBlockGrid->SetOwnerTable(this);
	}

	auto P0Location = DeckPlace1->GetComponentLocation();
	auto P1Location = DeckPlace2->GetComponentLocation();


	// create deck
	// Player0_Deck = GetWorld()->SpawnActor<AZDeck>(DeckKind, P0Location, FRotator::ZeroRotator);
	// if(Player0_Deck) 
	// 	Player0_Deck->Init(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//
	// Player1_Deck = GetWorld()->SpawnActor<AZDeck>(DeckKind, P1Location, FRotator::ZeroRotator);
	// if(Player1_Deck)
	// 	Player1_Deck->Init(UGameplayStatics::GetPlayerController(GetWorld(), 1));
	// ²âÊÔÖ¡Êý¿¨¶Ù


}

// Called every frame
void AZTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MyTimeline != NULL)
	{
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}


void AZTable::InitRoundCursor()
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;
	auto GameState = GetWorld()->GetGameState<AZGameState>();
	RoundTime = GameState->RoundTime;
	if (FloatCurve != NULL)
	{
		MyTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		this->BlueprintCreatedComponents.Add(MyTimeline); // Add to array so it gets saved
		MyTimeline->SetNetAddressable();	// This component has a stable name that can be referenced for replication

		MyTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
		MyTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		MyTimeline->SetLooping(false);
		//MyTimeline->SetTimelineLength(20.0f);
		auto line = MyTimeline->GetTimelineLength();

		MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		MyTimeline->SetPlaybackPosition(0.0f, false);

		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		MyTimeline->AddInterpFloat(FloatCurve, onTimelineCallback);
		MyTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		MyTimeline->RegisterComponent();
	}
	//PlayTimeline();

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentRoundCursor = GetWorld()->SpawnActor<AZRoundCursor>(RoundCursorKind, CursorBeginLocation, FRotator::ZeroRotator, SpawnParam);
}


#pragma region TimeLineAbout




void AZTable::TimelineCallback(float val)
{
	 FVector CursorTimeLine = FMath::Lerp(CursorBeginLocation, CursorEndLocation, val);
	 if (CurrentRoundCursor)
	 {
		 CurrentRoundCursor->SetActorLocation(CursorTimeLine);
	 }

}

void AZTable::TimelineFinishedCallback()
{
	UE_LOG(LogTemp, Log, TEXT("RoundCursor Timelind End"));
}


void AZTable::PlayTimeline()
{
	if (MyTimeline != NULL)
	{
		MyTimeline->PlayFromStart();
	}
}



void AZTable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZTable, CurrentZoneBlockGrid);
	//DOREPLIFETIME(ASCharacter, bDied);
}

#pragma endregion TimeLineAbout
