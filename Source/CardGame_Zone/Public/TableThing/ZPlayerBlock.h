// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZPlayerBlock.generated.h"





class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;
class AZZoneBlock;
UCLASS()
class CARDGAME_ZONE_API AZPlayerBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZPlayerBlock();
	void Init(int y,int x,bool BisBase,AZZoneBlock* OwnerZoneBlock,int PlayerOwner);
	void SetOwnerZoneBlock(AZZoneBlock *ZoneBlock);
	AZZoneBlock* GetOwnerZoneBlock();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable,WithValidation)
	void ServeActionExpansion();
	UFUNCTION(Server,Reliable,WithValidation)
	void ServeActionAnnexation(int y,int x);

	UFUNCTION(BlueprintCallable)
	void DoServeActionAnnexation(AZPlayerBlock* ChangePlayerBlock);
	UFUNCTION(BlueprintCallable)
	void DoServeActionExpansion();
	UFUNCTION(BlueprintCallable)
	void ActionAnnexation(int y,int x);
	UFUNCTION(BlueprintCallable)
	void ActionExpansion();
	UFUNCTION(BlueprintCallable)
	void ChangePlayerBlockOwner(AZPlayerBlock* ChangeToThisPlayerBlock);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Variable
public:
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent*SceneComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Block")
	bool BisPlayerOwner;
	UPROPERTY(BlueprintReadWrite)
	bool BisBaseBlock;
	// 0 - 1
	UPROPERTY(BlueprintReadWrite,Replicated)
	int PlayerOwner;

	//UPROPERTY(BlueprintReadWrite,Category = "")
	// In ZZoneBlockGrid -> ZoneBlockArray where  And in Game Where it is
	UPROPERTY(BlueprintReadWrite,Replicated)
	int GridY;
	UPROPERTY(BlueprintReadWrite,Replicated)
	int GridX;
	UPROPERTY(Replicated)
	AZZoneBlock* OwnerZoneBlock;
	
private:

	bool JudgeExpansion(int y,int x);
};



