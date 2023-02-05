// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RooterDrill.generated.h"

UCLASS()
class GLOBALGAMEJAM2023_API ARooterDrill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARooterDrill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* DrillMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
