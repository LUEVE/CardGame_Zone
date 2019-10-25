// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZCardBase.h"
#include "ZDeck.generated.h"

class UBoxComponent;
UCLASS()
class CARDGAME_ZONE_API AZDeck : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZDeck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Just for test;
	void InitDeck();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init(AActor* PlayerOwner);

	// Variable
public:
	UPROPERTY(Replicated)
	TArray<AZCardBase*> DeckCard;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly,Category = "Card")
	TSubclassOf<AZCardBase> DeckKind;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Card")
	int BeginCardNum;
	UPROPERTY(BlueprintReadWrite,Category = "Card")
	int NowCardNum;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Card")
	int CardInterval;


};


