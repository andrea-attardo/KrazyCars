// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PuzzlePlatformPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API APuzzlePlatformPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APuzzlePlatformPlayerController();

	

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

	virtual void PreClientTravel(const FString& PendingURL, ETravelType TravelType,bool bIsSeamlessTravel) override;

public:
	
	/*
	UFUNCTION(Client, Reliable)
	void CreateMainMenu();
	*/

	UFUNCTION()
	void ShowMainMenu();

	void SetIModeUI();

	void SetIModeGame();

	void SetPawnCameraBehind();

	void SetPawnCameraSetup();

	class UMainMenu* GetMenuAttachedTo() const { return Menu; }

private:
	//E' imppostato UEEditor
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainMenu> MenuClass;

	class UMainMenu* Menu;

	TArray<UActorComponent*> PawnCameras;
};
