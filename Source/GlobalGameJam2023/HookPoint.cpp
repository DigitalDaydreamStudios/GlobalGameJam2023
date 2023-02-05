// Fill out your copyright notice in the Description page of Project Settings.


#include "HookPoint.h"
#include "Components/BoxComponent.h"

// Sets default values
AHookPoint::AHookPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
}

// Called when the game starts or when spawned
void AHookPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHookPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), 10.f, 10, FColor(181, 0, 0), false, -1, 0, 2);
}

