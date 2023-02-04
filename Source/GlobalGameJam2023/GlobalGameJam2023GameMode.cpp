// Copyright Epic Games, Inc. All Rights Reserved.

#include "GlobalGameJam2023GameMode.h"
#include "RooterShooterPawn.h"
#include "UObject/ConstructorHelpers.h"

AGlobalGameJam2023GameMode::AGlobalGameJam2023GameMode()
{
	DefaultPawnClass = ARooterShooterPawn::StaticClass();

}
