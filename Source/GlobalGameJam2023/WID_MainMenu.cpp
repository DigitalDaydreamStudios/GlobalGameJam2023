// Fill out your copyright notice in the Description page of Project Settings.


#include "WID_MainMenu.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WID_Leaderboards.h"
#include "Blueprint/UserWidget.h"


void UWID_MainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    if (BTN_Play)
    {
        BTN_Play->OnClicked.AddDynamic(this, &UWID_MainMenu::PlayGame);
    }

    if (BTN_Options)
    {
        BTN_Options->OnClicked.AddDynamic(this, &UWID_MainMenu::OpenOptions);
    }

    if (BTN_Leaderboard)
    {
        BTN_Leaderboard->OnClicked.AddDynamic(this, &UWID_MainMenu::OpenLeaderboard);
    }

    if (BTN_Quit)
    {
        BTN_Quit->OnClicked.AddDynamic(this, &UWID_MainMenu::QuitGame);
    }


    static ConstructorHelpers::FClassFinder<UUserWidget> WID_Leaderboards(TEXT("/Game/UI/Widgets/WID_Leaderboards"));
	if (WID_Leaderboards.Class != NULL)
	{
		CustomUserWidgetClass = WID_Leaderboards.Class;
		LeaderboardWidget = CreateWidget<UCustomUserWidget>(GetWorld(), CustomUserWidgetClass);
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> WID_Options(TEXT("/Game/UI/Widgets/WID_Options"));
    if (WID_Options.Class != NULL)
    {
        CustomUserWidgetClass = WID_Options.Class;
        OptionsWidget = CreateWidget<UCustomUserWidget>(GetWorld(), CustomUserWidgetClass);
    }
}

void UWID_MainMenu::PlayGame()
{
    //Get the First Level from the DataTable DT_LevelList
    FName LevelName = "LEV_1";
    UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UWID_MainMenu::OpenOptions()
{
    if(IsValid(OptionsWidget))
    {
        OptionsWidget->AddToViewport();
    }
    //Remove self from viewport
    RemoveFromParent();
}

void UWID_MainMenu::OpenLeaderboard()
{
    if(IsValid(LeaderboardWidget))
    {
        LeaderboardWidget->AddToViewport();
    }
    //Remove self from viewport
    RemoveFromParent();
}

void UWID_MainMenu::QuitGame()
{
    //Exit the Game
    APlayerController* SpecificPlayer = GetWorld()->GetFirstPlayerController();
    UKismetSystemLibrary::QuitGame(GetWorld(), SpecificPlayer, EQuitPreference::Quit,true);
}