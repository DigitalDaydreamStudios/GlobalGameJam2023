// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

#include "GoalShip.generated.h"

UCLASS()
class GLOBALGAMEJAM2023_API AGoalShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Static Mesh Property for Ship
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship", meta = (Bind))
	// 	class UStaticMeshComponent* ShipMesh;
	
	//Static Mesh for GoalPlane
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship", meta = (Bind))
	// 	class UStaticMeshComponent* GoalPlane;

	//Function to check if player is overlapping with GoalPlane
	// UFUNCTION()
	// 	void OveralpWithPlayer();

};
