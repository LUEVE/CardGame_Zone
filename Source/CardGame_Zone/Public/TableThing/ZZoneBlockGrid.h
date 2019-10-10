// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZZoneBlockGrid.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AZZoneBlock;
class USceneComponent;
class AZPlayerBlock;
class AZTable;
USTRUCT(BlueprintType)
struct FZoneBlockArrayRow
{ 	
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<AZZoneBlock*>  Array;
};

UCLASS()
class CARDGAME_ZONE_API AZZoneBlockGrid : public AActor
{
	GENERATED_BODY()

	friend class AZPlayerBlock;
	friend class AZGameMode;
public:	
	// Sets default values for this actor's properties
	AZZoneBlockGrid();
	void SetOwnerTable(AZTable* Table);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitZoneBlockGrid();
	bool InitPlayerBaseZone();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Variable
public:

protected:
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category = "Component")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category = "Component")
	USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly,Category = "ZoneBlock")
	TSubclassOf<AZZoneBlock> ZoneBlock;
	// UPROPERTY(EditDefaultsOnly, Category = "ZoneBlock")
	// TSubclassOf<AZPlayerBlock> BasePlayerBlock;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Replicated)
	TArray<FZoneBlockArrayRow> ZoneBlocksArray;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ZoneBlock")
	int BlockSpaceX;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ZoneBlock")
	int BlockSpaceY;

	AZTable* OwnerTable;
private:
	int GridSize;

	bool BisInit;
};
