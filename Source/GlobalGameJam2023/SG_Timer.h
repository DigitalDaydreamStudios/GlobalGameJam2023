// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SG_Timer.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMEJAM2023_API USG_Timer : public USaveGame
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
    FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
	float Time;

	USG_Timer();
};
