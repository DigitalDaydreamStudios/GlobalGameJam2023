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
		UCustomUserWidget* Widget = CreateWidget<UCustomUserWidget>(GetWorld(), CustomUserWidgetClass);
		if(IsValid(Widget))
		{
			Widget->AddToViewport();
		}
	}else{
		UE_LOG(LogTemp, Warning, TEXT("Hello: I'm a MenuHandler, but I don't have a WidgetClass"));
	}
}


// Called when the game starts
void UMenuHandler::BeginPlay()
{
	Super::BeginPlay();

	// if(IsValid(WidgetClass))
	// {
	// 	UCustomUserWidget* Widget = CreateWidget<WID_MainMenu>(GetWorld(), WidgetClass);
	// 	if(IsValid(Widget))
	// 	{
	// 		Widget->AddToViewport();
	// 		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello: I'm a MenuHandler, and I have a WidgetClass"));
	// 	}else {
	// 		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello: I'm a MenuHandler, but I don't have a WidgetClass"));
	// 	}
	// }
	// else
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello: I'm a MenuHandler, but I don't have a WidgetClass"));
	// }

}