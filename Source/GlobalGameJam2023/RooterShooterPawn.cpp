// Fill out your copyright notice in the Description page of Project Settings.


#include "RooterShooterPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HookPoint.h"
#include "CableComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "RooterPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h" 


// Sets default values
ARooterShooterPawn::ARooterShooterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Capsule->SetSimulatePhysics(true);

	if(Capsule == nullptr){ UE_LOG(LogTemp, Warning, TEXT("CAPSULE NULL!")); }
	

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Capsule);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Capsule);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Cable = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	Cable->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//Cable->SetComponentTickEnabled(false);
	//Cable->SetVisibility(false);

	PhysRope = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysRope"));


	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	MoveScale = 1.f;
}

// Called when the game starts or when spawned
void ARooterShooterPawn::BeginPlay()
{
	Super::BeginPlay();
	
	HookPoint = GetWorld()->SpawnActor<AHookPoint>(AHookPoint::StaticClass());
}

// Called every frame
void ARooterShooterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (HookedActor != nullptr) {
		Cable->EndLocation = HookedActor->GetActorLocation() - GetActorLocation();
	}*/
}

// Called to bind functionality to input
void ARooterShooterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//APlayerController* RPC = Cast<APlayerController>(Controller);
	ARooterPlayerController* RPC = Cast<ARooterPlayerController>(Controller);
	
	if (RPC != nullptr) {
		check(EIC && RPC);
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARooterShooterPawn::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARooterShooterPawn::Look);
		EIC->BindAction(ShootAction, ETriggerEvent::Started, this, &ARooterShooterPawn::Shoot);

		ULocalPlayer* LocalPlayer = RPC->GetLocalPlayer();
		check(LocalPlayer);
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	else{ UE_LOG(LogTemp, Warning, TEXT("Make Sure Controller is set to ARooterPlayerController")); }
}

void ARooterShooterPawn::Move(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FInputActionValue::Axis3D>();

	//AddMovementInput(GetActorRotation().RotateVector(Input), MoveScale);

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ARooterShooterPawn::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARooterShooterPawn::Shoot() {
	UE_LOG(LogTemp, Warning, TEXT("Shooot!"));

	FHitResult Hit;
	FVector offset = FVector(0.f,0.f,50.f);
	FVector TraceStart = GetActorLocation() + offset;
	FVector TraceEnd = (GetActorLocation() + offset) + (FollowCamera->GetForwardVector() * ShootDistance);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	if (Hit.bBlockingHit) {
		UE_LOG(LogTemp, Warning, TEXT("HIT!"));

		HookedActor = Hit.GetActor();

		////CompClass can be a BP
		//UPrimitiveComponent* NewHookComponent = NewObject<UPrimitiveComponent>(HookedActor);
		//if (!NewHookComponent)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Attach Location Creation Failed!"));
		//}
		////~~~~~~~~~~~~~

		//NewHookComponent->SetupAttachment(HookedActor->GetRootComponent());
		//NewHookComponent->RegisterComponent();
		//HookedActor->AddInstanceComponent(NewHookComponent);
		//NewHookComponent->SetRelativeLocation(Hit.Location-HookedActor->GetActorLocation());
		//NewHookComponent->Rename(TEXT("HookPoint"));

		if (HookPoint != nullptr) {
			HookPoint->SetActorLocation(Hit.Location);

			HookPoint->AttachToActor(Hit.GetActor(),FAttachmentTransformRules::KeepWorldTransform);

			Cable->SetAttachEndTo(HookPoint, FName(TEXT("Box")), FName(TEXT("")));

			PhysRope->ConstraintActor1 = HookPoint;
			PhysRope->ConstraintActor2 = this;
			PhysRope->SetAngularSwing1Limit(ACM_Limited, 20.f);
			PhysRope->SetAngularSwing2Limit(ACM_Limited, 40.f);
			PhysRope->SetDisableCollision(true);
			PhysRope->SetConstrainedComponents(
				Cast<UPrimitiveComponent>(HookPoint->GetRootComponent()), TEXT("Box"),
				Cast<UPrimitiveComponent>(Capsule),TEXT("Capsule"));
			PhysRope->SetWorldLocation((GetActorLocation()+HookedActor->GetActorLocation()) * 0.5f);
		}

		//Cable->SetAttachEndTo(Hit.GetActor(), FName(TEXT("HookPoint")), FName(TEXT("")));

		//PhysRope->ConstraintActor1 = Hit.GetActor();
		//PhysRope->ConstraintActor2 = this;
		//PhysRope->SetAngularSwing1Limit(ACM_Limited, 20.f);
		//PhysRope->SetAngularSwing2Limit(ACM_Limited, 40.f);
		//PhysRope->SetDisableCollision(true);
		//PhysRope->SetConstrainedComponents(
		//	//Cast<UPrimitiveComponent>(Hit.GetActor()->GetComponentByClass(UBoxComponent::StaticClass())),TEXT("Box"),
		//	Cast<UPrimitiveComponent>(NewHookComponent), TEXT("HookPoint"),
		//	Cast<UPrimitiveComponent>(Capsule),TEXT("Capsule"));
		//PhysRope->SetWorldLocation((GetActorLocation()+HookedActor->GetActorLocation()) * 0.5f);
	}
}

void ARooterShooterPawn::CreatePhysConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA)
{
	//set up the constraint instance with all the desired values
	FConstraintInstance ConstraintInstance;

	//set values here, see functions I am sharing with you below
	//UYourStaticLibrary::SetLinearLimits(ConstraintInstance, ...); //or make the functions below non static
	//UYourStaticLibrary::SetAngularLimits(ConstraintInstance, ...);


		//New Object
	UPhysicsConstraintComponent* ConstraintComp = NewObject<UPhysicsConstraintComponent>(RootSMA);
	if (!ConstraintComp)
	{
		//UE_LOG constraint UObject could not be created!
		return;
	}

	////~~~~~~~~~~~~~~~~~~~~~~~~
	////Set Constraint Instance!
	//ConstraintComp->ConstraintInstance = ConstraintInstance;
	////~~~~~~~~~~~~~~~~~~~~~~~~

	////Set World Location
	//ConstraintComp->SetWorldLocation(RootSMA->GetActorLocation());

	////Attach to Root!
	//ConstraintComp->AttachTo(RootSMA->GetRootComponent(), NAME_None, EAttachLocation::KeepWorldPosition);

	////~~~ Init Constraint ~~~
	//ConstraintComp->SetConstrainedComponents(RootSMA->StaticMeshComponent, NAME_None, TargetSMA->StaticMeshComponent, NAME_None);
}