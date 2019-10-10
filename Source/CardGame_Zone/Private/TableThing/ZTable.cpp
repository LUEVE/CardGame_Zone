// Fill out your copyright notice in the Description page of Project Settings.


#include "ZTable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ZZoneBlockGrid.h"
#include "UnrealNetwork.h"

// Sets default values
AZTable::AZTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComp"));

	RootComponent = MeshComponent;
	BoxComponent->SetupAttachment(MeshComponent);

	SetReplicates(true);

}

// Called when the game starts or when spawned
void AZTable::BeginPlay()
{
	Super::BeginPlay();
	
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


}

// Called every frame
void AZTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AZTable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZTable, CurrentZoneBlockGrid);
	//DOREPLIFETIME(ASCharacter, bDied);
}
