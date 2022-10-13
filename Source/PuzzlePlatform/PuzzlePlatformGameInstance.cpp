// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"



UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance()
{
    
}

void UPuzzlePlatformGameInstance::Init()
{
    //UE_LOG(LogTemp, Warning, TEXT("Class found: %s"), *MainMenuClass->GetName());
    
}



void UPuzzlePlatformGameInstance::Host()
{
    GetEngine()->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, TEXT("Server is travelling new map" ));

    GetWorld()->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"));

}


void UPuzzlePlatformGameInstance::Join(const FString& IPAddress)
{
    GetEngine()->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString::Printf(TEXT("Joining %s"), *IPAddress));

    APlayerController* PlayerController = GetFirstLocalPlayerController(GetWorld());
    if (PlayerController)
    { 
        PlayerController->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
    }
}