// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Engine/StaticMeshActor.h"
#include "Components/CapsuleComponent.h"
#include "RooterShooterPawn.generated.h"

UCLASS()
class GLOBALGAMEJAM2023_API ARooterShooterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARooterShooterPawn();

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	///** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	class UCableComponent* Cable;

	UPROPERTY(EditAnywhere)
	class UPhysicsConstraintComponent* PhysRope;

	UPROPERTY(EditAnywhere)
	float MoveScale;

	UPROPERTY(EditAnywhere)
	float ShootDistance = 1000.f;

	class AActor* HookedActor;

protected:
	class UPhysicsConstraintComponent* PhysConstraint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// Shoot action
	void Shoot();

	void CreatePhysConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
