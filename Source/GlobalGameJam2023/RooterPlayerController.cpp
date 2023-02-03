// Fill out your copyright notice in the Description page of Project Settings.


#include "RooterPlayerController.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"

void ARooterPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	PawnMappingContext = NewObject<UInputMappingContext>(this);

	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	PawnMappingContext->MapKey(MoveAction, EKeys::W);
}