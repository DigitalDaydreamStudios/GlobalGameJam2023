// Fill out your copyright notice in the Description page of Project Settings.


#include "RooterDrill.h"

// Sets default values
ARooterDrill::ARooterDrill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DrillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrillMesh"));
	SetRootComponent(DrillMesh);
}

// Called when the game starts or when spawned
void ARooterDrill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARooterDrill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

