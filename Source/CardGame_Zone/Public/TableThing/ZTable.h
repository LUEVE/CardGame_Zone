// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZDeck.h"
#include "Components/TimelineComponent.h"
//#include "Components/TimelineComponent.h"
#include "ZTable.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class USceneComponent;
class UBoxComponent;
class AZZoneBlockGrid;
class AZRoundCursor;
UCLASS()
class CARDGAME_ZONE_API AZTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZTable();
	void PlayTimeline();
	UFUNCTION(BlueprintCallable)
	void InitTable();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UFUNCTION(BlueprintCallable)



	UFUNCTION()
	void TimelineCallback(float val);
	UFUNCTION()
	void TimelineFinishedCallback();
	void InitRoundCursor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

// Variable
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent *DeckPlace1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent *DeckPlace2;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Component")
	UStaticMeshComponent *MeshComponent;




	TSubclassOf<AZZoneBlockGrid> ZoneBlockGrid;
	UPROPERTY(BlueprintReadOnly,Replicated)
	AZZoneBlockGrid* CurrentZoneBlockGrid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent*SceneComponent;
	UPROPERTY(EditDefaultsOnly, Category = "RoundCursor")
	TSubclassOf<AZRoundCursor> RoundCursorKind;
	UPROPERTY(BlueprintReadWrite)
	AZRoundCursor* CurrentRoundCursor;
	UPROPERTY(EditDefaultsOnly, Category = "RoundCursor")
	FVector CursorBeginLocation;
	UPROPERTY(EditDefaultsOnly, Category = "RoundCursor")
	FVector CursorEndLocation;

 

	// timeLine
	UPROPERTY()
	UTimelineComponent* MyTimeline;

	UPROPERTY()
	UCurveFloat* FloatCurve;



	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	// --timeLind
	UPROPERTY(BlueprintReadOnly)
		float RoundTime;


	// ≤‚ ‘”√
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AZDeck> DeckKind;
	AZDeck* Player0_Deck;
	AZDeck* Player1_Deck;

	//
private:



};
