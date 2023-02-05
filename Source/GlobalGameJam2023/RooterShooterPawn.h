// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Engine/StaticMeshActor.h"
#include "Components/CapsuleComponent.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include "MenuHandler.h"
#include "RooterShooterPawn.generated.h"

UCLASS()
class GLOBALGAMEJAM2023_API ARooterShooterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARooterShooterPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* DrillMesh;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
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

	/** Pull Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PullAction;

	/** Pull Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ResetAction;


	UPROPERTY(EditAnywhere)
	class UCableComponent* Cable;

	UPROPERTY(EditAnywhere)
	class UPhysicsConstraintComponent* PhysRope;

	UPROPERTY(EditAnywhere)
	float MoveScale = 0.f;

	UPROPERTY(EditAnywhere)
	float PullStrength = 500.f;

	UPROPERTY(EditAnywhere)
	UMenuHandler* MenuHandler;

	UPROPERTY(EditAnywhere)
	float ShootDistance = 3000.f;

	class AActor* HookedActor;

	UPROPERTY(EditAnywhere)
	class AHookPoint* HookPoint;

	//UPROPERTY(EditAnywhere)
	//class ARooterDrill* RooterDrill;


protected:
	class UPhysicsConstraintComponent* PhysConstraint;

	bool IsRooted;

	bool CanShoot;

	FTimerHandle ShootTimerHandle;

	FConstraintInstance ConstraintInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// Shoot action
	void Shoot();

	// Pull action
	void Pull();

	UFUNCTION(BlueprintImplementableEvent)
	void Reset();

	void ResetCanShoot();

	void CreatePhysConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA);

	void SetupConstraintInstance();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
