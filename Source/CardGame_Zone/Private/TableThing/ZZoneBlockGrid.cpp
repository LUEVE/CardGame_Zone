// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TableThing/ZZoneBlockGrid.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "ZTable.h"
#include "ZZoneBlock.h"
#include "UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "ZPlayerBlock.h"
// Sets default values
AZZoneBlockGrid::AZZoneBlockGrid():
BlockSpaceX(200)
,BlockSpaceY(200)
,GridSize(5)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = SceneComponent;
	MeshComponent->SetupAttachment(RootComponent);
	BisInit = false;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AZZoneBlockGrid::BeginPlay()
{
	Super::BeginPlay();
	if (Role == ROLE_Authority)
	{
		InitZoneBlockGrid();
		//InitPlayerBaseZone();
	}
	auto t = GetOwner();
}

void AZZoneBlockGrid::InitZoneBlockGrid()
{
	int Size = GridSize;
	ZoneBlocksArray.SetNum(Size);
	for (int i = 0; i < Size; i++)
		ZoneBlocksArray[i].Array.SetNum(Size);

	FVector GridLocation =  GetActorLocation();
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int y = 0; y < Size;y++)
		for (int x = 0;x <Size;x++)
		{
			FVector TempLocation = GridLocation + FVector(y*BlockSpaceY, x*BlockSpaceX, 0);
			ZoneBlocksArray[y].Array[x] = GetWorld()->SpawnActor<AZZoneBlock>(ZoneBlock,TempLocation,FRotator::ZeroRotator,SpawnParam);
		//	ZoneBlocksArray[y].Array[x]->SetOwnerZoneBlockGrid(this);
			if (ZoneBlocksArray[y].Array[x])
			{
				bool BisBase = ((y == 0 || y == 4) && (x >= 1 && x <= 3));
				if (BisBase && y == 0)
				{
					ZoneBlocksArray[y].Array[x]->Init(y, x, EZoneBlockKind::BaseBlock_Player0,this);
				}
				else if(BisBase && y == 4)
				{
					ZoneBlocksArray[y].Array[x]->Init(y, x, EZoneBlockKind::BaseBlock_Player1, this);
				}
				else
				{
					ZoneBlocksArray[y].Array[x]->Init(y, x, EZoneBlockKind::NormalBlock,this);
				}

			}
		}
	

	BisInit = true;
}

bool AZZoneBlockGrid::InitPlayerBaseZone()
{
	if (BisInit)
	{
		// player0
		for (int i =  1; i <= 3 ; ++i)
		{
			ZoneBlocksArray[0].Array[i]->CreateBaseBlock(0);
			ZoneBlocksArray[0].Array[i]->CurrentPlayerBlock->SetOwner(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		}
		//player1
		for (int i = 1; i <= 3; i++)
		{
			ZoneBlocksArray[4].Array[i]->CreateBaseBlock(1);
			ZoneBlocksArray[4].Array[i]->CurrentPlayerBlock->SetOwner(UGameplayStatics::GetPlayerController(GetWorld(), 1));
		}
		return true;
	}
	return false;
}

void AZZoneBlockGrid::SetOwnerTable(AZTable *Table)
{
	OwnerTable = Table;
}


// Called every frame
void AZZoneBlockGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AZZoneBlockGrid::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZZoneBlockGrid, ZoneBlocksArray);
}

