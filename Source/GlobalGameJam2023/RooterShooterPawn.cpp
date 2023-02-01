// Fill out your copyright notice in the Description page of Project Settings.


#include "RooterShooterPawn.h"

// Sets default values
ARooterShooterPawn::ARooterShooterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARooterShooterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARooterShooterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARooterShooterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

