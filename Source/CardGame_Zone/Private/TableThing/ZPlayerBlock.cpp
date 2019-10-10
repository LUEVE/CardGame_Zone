// Fill out your copyright notice in the Description page of Project Settings.


#include "ZPlayerBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ZZoneBlockGrid.h"
#include "ZZoneBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealNetwork.h"
// Sets default values
AZPlayerBlock::AZPlayerBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	PlayerOwner = -1;
	RootComponent = SceneComponent;
	BoxComponent->SetupAttachment(RootComponent);
	MeshComponent->SetupAttachment(RootComponent);
	SetReplicates(true);
}

void AZPlayerBlock::Init(int y, int x, bool BisBase,AZZoneBlock* OwnerZoneBlock,int PlayerOwner)
{
	GridY = y;
	GridX = x;
	BisBaseBlock = BisBase;
	this->PlayerOwner = PlayerOwner;
	SetOwnerZoneBlock(OwnerZoneBlock);
	SetOwner(UGameplayStatics::GetPlayerController(GetWorld(),PlayerOwner));
}

void AZPlayerBlock::SetOwnerZoneBlock(AZZoneBlock* ZoneBlock)
{
	OwnerZoneBlock = ZoneBlock;
}

AZZoneBlock* AZPlayerBlock::GetOwnerZoneBlock()
{
	return OwnerZoneBlock;
}

// Called when the game starts or when spawned
void AZPlayerBlock::BeginPlay()
{
	Super::BeginPlay();
	// will change owner ,maybe should change to player or pawn or character
	
}


void AZPlayerBlock::DoServeActionExpansion()
{
	auto t = GetOwner();
	ServeActionExpansion();
}

void AZPlayerBlock::ActionAnnexation()
{
	if (OwnerZoneBlock)
	{
		
	}

}
void AZPlayerBlock::ActionExpansion()
{


	if (OwnerZoneBlock)
	{
		auto& TempArray = OwnerZoneBlock->GetOwnerZoneBlockGrid()->ZoneBlocksArray;
		int foot[5][2] = { {0,1},{0,-1},{1,0},{-1,0} };
		for (int i = 0; i < 5; i++)
		{
			int y = GridY + foot[i][1];
			int x = GridX + foot[i][0];
			if (JudgeExpansion(y, x))
			{
				TempArray[y].Array[x]->CreateNormalBlock(PlayerOwner);
			}
		}
	}
}

void AZPlayerBlock::ServeActionExpansion_Implementation()
{
	//ActionExpansion();
	if (OwnerZoneBlock)
	{
		auto& TempArray = OwnerZoneBlock->GetOwnerZoneBlockGrid()->ZoneBlocksArray;
		int foot[5][2] = { {0,1},{0,-1},{1,0},{-1,0} };
		for (int i = 0; i < 5; i++)
		{
			int y = GridY + foot[i][1];
			int x = GridX + foot[i][0];
			if (JudgeExpansion(y, x))
			{
				TempArray[y].Array[x]->CreateNormalBlock(PlayerOwner);
			}
		}
	}
}


bool AZPlayerBlock::ServeActionExpansion_Validate()
{
	return true;
}

// Called every frame
void AZPlayerBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AZPlayerBlock::JudgeExpansion(int y, int x)
{
	if (y < 0 || y >4 || x < 0 || x > 4)
		return false;
	return true;
}

void AZPlayerBlock::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZPlayerBlock, OwnerZoneBlock);
	DOREPLIFETIME(AZPlayerBlock, PlayerOwner);
	DOREPLIFETIME(AZPlayerBlock, GridX);
	DOREPLIFETIME(AZPlayerBlock, GridY);
}

