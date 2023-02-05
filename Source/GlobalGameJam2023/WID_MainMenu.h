// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUserWidget.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "WID_MainMenu.generated.h"
/**
 * 
 */
UCLASS()
class GLOBALGAMEJAM2023_API UWID_MainMenu : public UCustomUserWidget
{
	GENERATED_BODY()

protected:	
	UFUNCTION()
	void NativeConstruct();

	//Bind the UIButton BTN_Play to the function PlayGame
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN_Play;

	//Bind the UIButton BTN_Quit to the function QuitGame
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN_Quit;

	//Bind the UIButton BTN_Options to the function OpenOptions
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN_Options;

	//Bind the UIButton BTN_Leaderboard to the function OpenLeaderboard
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN_Leaderboard;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UCustomUserWidget* LeaderboardWidget;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UCustomUserWidget* OptionsWidget;
	
	TSubclassOf<class UUserWidget> CustomUserWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UCustomUserWidget* CustomUserWidget_Leaderboard;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UCustomUserWidget* CustomUserWidget_Options;

	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void OpenOptions();

	UFUNCTION()
	void OpenLeaderboard();
};
