// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMEJAM2023_API ARooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

	UPROPERTY()
	class UInputMappingContext* PawnMappingContext;
	
	UPROPERTY()
	class UInputAction* MoveAction;
};
