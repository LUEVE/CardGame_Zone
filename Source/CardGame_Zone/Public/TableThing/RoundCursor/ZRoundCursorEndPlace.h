// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZRoundCursorEndPlace.generated.h"


class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;

UCLASS()
class CARDGAME_ZONE_API AZRoundCursorEndPlace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZRoundCursorEndPlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
//variable
public:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* BoxComponent;
};
