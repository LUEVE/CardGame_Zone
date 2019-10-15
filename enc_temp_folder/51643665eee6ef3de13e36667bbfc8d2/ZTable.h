// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZTable.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AZZoneBlockGrid;
class UBoxComponent;

UCLASS()
class CARDGAME_ZONE_API AZTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UFUNCTION(BlueprintCallable)
	void InitTable();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// Variable
public:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Component")
	UStaticMeshComponent *MeshComponent;
	TSubclassOf<AZZoneBlockGrid> ZoneBlockGrid;
	UPROPERTY(BlueprintReadOnly,Replicated)
	AZZoneBlockGrid* CurrentZoneBlockGrid;

private:
	


};
