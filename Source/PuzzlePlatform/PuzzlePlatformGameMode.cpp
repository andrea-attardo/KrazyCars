// Copyright Epic Games, Inc. All Rights Reserved.


#include "PuzzlePlatformGameMode.h"
#include "PuzzlePlatformCharacter.h"
#include "PuzzlePlatformGameInstance.h"
#include "PuzzlePlatformPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

APuzzlePlatformGameMode::APuzzlePlatformGameMode()
{
	// set default pawn class 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_Car"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void APuzzlePlatformGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);


	/*
	if (UGameplayStatics::GetCurrentLevelName(this, true) == "Menu")
	{ 
		Cast<APuzzlePlatformPlayerController>(NewPlayer)->LoadMainMenu();
		Cast<APuzzlePlatformPlayerController>(NewPlayer)->SetIModeUI();
	}
	else 
	{
		Cast<APuzzlePlatformPlayerController>(NewPlayer)->SetIModeGame();
	}
	*/
}


