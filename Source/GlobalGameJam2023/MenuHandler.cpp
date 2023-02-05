// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuHandler.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UMenuHandler::UMenuHandler()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello: I'm a MenuHandler"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WID_MainMenu(TEXT("/Game/UI/Widgets/WID_MainMenu"));
	if (WID_MainMenu.Class != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello: I'm a MenuHandler, and I have a WidgetClass"));
		CustomUserWidgetClass = WID_MainMenu.Class;
		CustomUserWidget = CreateWidget<UCustomUserWidget>(GetWorld(), CustomUserWidgetClass);
		if(IsValid(CustomUserWidget))
		{
			//check what level we are on and load the correct widget
			if (GetWorld()->GetName() == "LEV_MainMenu"){
				UE_LOG(LogTemp, Warning, TEXT("Hello:I'm on the main menu level and I'm loading the main menu widget"));
				CustomUserWidget->AddToViewport();
				// show mouse cursor
				if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
				{
					PlayerController->bShowMouseCursor = true;
					PlayerController->bEnableClickEvents = true;
					PlayerController->bEnableMouseOverEvents = true;
				}

			}else{
				UE_LOG(LogTemp, Warning, TEXT("Hello:I'm not on the main menu level and I'm not loading the main menu widget"));
			}
		}
	}else{
		UE_LOG(LogTemp, Warning, TEXT("Hello: I'm a MenuHandler, but I don't have a WidgetClass"));
	}
}

// Called when the game starts
void UMenuHandler::BeginPlay()
{
	Super::BeginPlay();
}