// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZCardBase.generated.h"
class UBoxComponent;
UCLASS()
class CARDGAME_ZONE_API AZCardBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZCardBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ChangeMaterial();
//variable
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* CardBackComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* CardFaceComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
	UMaterialInterface* CardMaterial;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Speed")
	float Speed;
};
