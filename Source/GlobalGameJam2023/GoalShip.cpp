// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalShip.h"
#include "Engine/World.h"

// Sets default values
AGoalShip::AGoalShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// //Get player pawn
	// AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	// if (IsValid(Player)){

	// 	if (IsValid(GoalPlane)){
	// 		//Add Check for when Player Overlaps with GoalPlane
	// 		GoalPlane->OnComponentBeginOverlap.AddDynamic(this, &AGoalShip::OveralpWithPlayer);
	// 	}
	// }

}

// Called when the game starts or when spawned
void AGoalShip::BeginPlay()
{
	Super::BeginPlay();	
}

// void AGoalShip::OveralpWithPlayer()
// {
// 	//Get player pawn
// 	AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();

// 	//Check if player is overlapping with GoalPlane
// 	if (Player->IsOverlappingActor(GoalPlane)){
// 		UE_LOG(LogTemp, Warning, TEXT("Player is overlapping with GoalPlane"));
// 		//If player is overlapping with GoalPlane, then call the function to Go to next level
// 	}
// }