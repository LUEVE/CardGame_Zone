// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZZoneBlock.generated.h"

UENUM(BlueprintType)
enum class EZoneBlockKind :uint8
{
	NormalBlock,

	BaseBlock_Player0,

	BaseBlock_Player1,

	SpecialBlock2,
};

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;
class AZPlayerBlock;
class AZZoneBlockGrid;
UCLASS()
class CARDGAME_ZONE_API AZZoneBlock : public AActor
{
	GENERATED_BODY()
	
public:
	friend class AZPlayerBlock;
	// Sets default values for this actor's properties
	AZZoneBlock();
	void Init(int y,int x,EZoneBlockKind BlockKind);
	void Init(int y, int x, EZoneBlockKind BlockKind, AZZoneBlockGrid* OwnerBlockGrid);
	void InitBaseBlockPlace(int BaseBlockOwner);
	void InitNormalBlockPlace();
	// 0 or 1
	void CreateBaseBlock(int Player);
	
	void CreateNormalBlock(int Player);


	void SetOwnerZoneBlockGrid(AZZoneBlockGrid* BlockGrid);
	AZZoneBlockGrid* GetOwnerZoneBlockGrid();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitZoneBlock();
	void ChangeCurrentPlayerBlock(int ToPlayer);
	void DestroyCurrentPlayerBlock();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Block")
	bool bHasBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Block")
	bool bHasBaseBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Block")
	bool BIsBaseBlockPlace;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Replicated, Category = "Block")
	AZPlayerBlock* CurrentPlayerBlock;

protected:
	int GridX;
	int GridY;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Component")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent*SceneComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Block")
	TSubclassOf<AZPlayerBlock> BaseBlock_Player0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Block")
	TSubclassOf<AZPlayerBlock> NormalBlock_Player0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Block")
	TSubclassOf<AZPlayerBlock> BaseBlock_Player1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Block")
	TSubclassOf<AZPlayerBlock> NormalBlock_Player1;

	
	
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	FVector CreatePlayerBlockLocation;

	// -1 Not A BaseBlock Place, 0 player0 can create BaseBlock,1 player1 can do . 
	int BaseBlockOwner;
	
	AZZoneBlockGrid* OwnerBlockGrid;
private:
};
