// Fill out your copyright notice in the Description page of Project Settings.


#include "ZZoneBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "ZPlayerBlock.h"
#include "UnrealNetwork.h"
#include "ZZoneBlockGrid.h"
// Sets default values

AZZoneBlock::AZZoneBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComp"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComponent;
	BoxComponent->SetupAttachment(RootComponent);
	MeshComponent->SetupAttachment(RootComponent);

	bHasBlock = false;
	//RootComponent->SetupAttachment(StaticComponent);
	SetReplicates(true);
//	SetReplicateMovement(true);
}

void AZZoneBlock::Init(int y,int x,EZoneBlockKind BlockKind)
{
	
	GridX = x;
	GridY = y;
	switch (BlockKind)
	{
		case EZoneBlockKind::BaseBlock_Player0:
			InitBaseBlockPlace(0);
			break;
		case EZoneBlockKind::BaseBlock_Player1:
			InitBaseBlockPlace(1);
			break;;
		case EZoneBlockKind::NormalBlock:
			InitNormalBlockPlace();
			break;
		default :
			UE_LOG(LogTemp, Log, TEXT("ZoneBlock isn't init"));
	}
}

void AZZoneBlock::Init(int y, int x, EZoneBlockKind BlockKind, AZZoneBlockGrid* OwnerBlockGrid)
{
	Init(y, x, BlockKind);
	SetOwnerZoneBlockGrid(OwnerBlockGrid);
	// will change owner
	//AActor * temp = OwnerBlockGrid;
	SetOwner(OwnerBlockGrid);
}


void AZZoneBlock::InitBaseBlockPlace(int BaseBlockOwner)
{
	BIsBaseBlockPlace = true;
	this->BaseBlockOwner = BaseBlockOwner;
}

void AZZoneBlock::InitNormalBlockPlace()
{
	BIsBaseBlockPlace = false;
}

void AZZoneBlock::CreateBaseBlock(int Player)
{
	auto& BaseBlock = BaseBlock_Player0;
	if (Player)
	{
		BaseBlock = BaseBlock_Player1;
	}
	if (BaseBlock == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("BaseBlock is nullptr, please see whether set BaseBlock"));
		return;
	}

	if (!bHasBlock && !bHasBaseBlock && BIsBaseBlockPlace)
	{
		bHasBaseBlock = true;
		bHasBlock = true;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		CurrentPlayerBlock = GetWorld()->SpawnActor<AZPlayerBlock>(BaseBlock, CreatePlayerBlockLocation, GetActorRotation(), SpawnParameters);
		CurrentPlayerBlock->Init(GridY,GridX,BIsBaseBlockPlace,this,Player);
	}
}

void AZZoneBlock::CreateNormalBlock(int Player)
{
	auto& NormalBlock = NormalBlock_Player0;
	if (Player)
	{
		NormalBlock = NormalBlock_Player1;
	}
	if (NormalBlock == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("NormalBlock is nullptr, please see whether set NormalBlock"));
		return;
	}
	if (!bHasBlock && !BIsBaseBlockPlace)
	{
		bHasBlock = true;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		CurrentPlayerBlock = GetWorld()->SpawnActor<AZPlayerBlock>(NormalBlock, CreatePlayerBlockLocation, GetActorRotation(), SpawnParameters);
		CurrentPlayerBlock->Init(GridY, GridX, BIsBaseBlockPlace,this,Player);
	}
}

void AZZoneBlock::SetOwnerZoneBlockGrid(AZZoneBlockGrid* BlockGrid)
{
	OwnerBlockGrid = BlockGrid;
}

AZZoneBlockGrid* AZZoneBlock::GetOwnerZoneBlockGrid()
{
	return OwnerBlockGrid;
}

// Called when the game starts or when spawned
void AZZoneBlock::BeginPlay()
{


	Super::BeginPlay();
	CreatePlayerBlockLocation = GetActorLocation() + FVector(0.0, 0.0, 20.0);
	InitZoneBlock();
}

void AZZoneBlock::InitZoneBlock()
{

}

// Called every frame
void AZZoneBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZZoneBlock::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZZoneBlock, CurrentPlayerBlock);
}

