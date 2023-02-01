// Copyright Epic Games, Inc. All Rights Reserved.

#include "GlobalGameJam2023GameMode.h"
#include "GlobalGameJam2023Character.h"
#include "UObject/ConstructorHelpers.h"

AGlobalGameJam2023GameMode::AGlobalGameJam2023GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
