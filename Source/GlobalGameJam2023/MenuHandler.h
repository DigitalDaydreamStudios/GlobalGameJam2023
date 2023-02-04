// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUserWidget.h"
#include "Components/ActorComponent.h"
#include "MenuHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLOBALGAMEJAM2023_API UMenuHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMenuHandler();
	
	TSubclassOf<class UUserWidget> CustomUserWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UCustomUserWidget* CustomUserWidget;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
