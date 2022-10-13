// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"


APuzzlePlatformPlayerController::APuzzlePlatformPlayerController()
{   
    if (!IsTemplate())
    { 
        UE_LOG(LogTemp, Warning, TEXT("One Player Controller created"));
    }
}

void APuzzlePlatformPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (IsLocalController())
    { 
        InputComponent->BindAction("ShowMainMenu", IE_Pressed, this, &APuzzlePlatformPlayerController::ShowMainMenu);
    }
}

void APuzzlePlatformPlayerController::PreClientTravel(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel)
{
    /**/
    
}

void APuzzlePlatformPlayerController::BeginPlay()
{
    
    if (IsLocalController())
    { 
        
        if (MenuClass && !Menu)
        {
            UE_LOG(LogTemp, Warning, TEXT("Widget Created"));

            Menu = CreateWidget<UMainMenu>(this, MenuClass);
            Menu->bIsFocusable = true;     
        }
        
        
        if ( APawn* CarPawn = GetPawn() )
        { 
            PawnCameras = CarPawn->GetComponentsByTag(UCameraComponent::StaticClass(), "CameraPawn");
        }
    }
    
}



/*
void APuzzlePlatformPlayerController::CreateMainMenu_Implementation()
{   
    
    ConstructorHelpers::FClassFinder<UMainMenu> BPWMainMenuClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
    if (BPWMainMenuClass.Succeeded())
    {
        MainMenuClass = BPWMainMenuClass.Class;
    }
    

    if (MenuClass)
    { 
        Menu = CreateWidget<UMainMenu>(this, MenuClass);
        if (Menu)
        {
            Menu->bIsFocusable = true;  
        }
    }
    
}
*/

void APuzzlePlatformPlayerController::ShowMainMenu()
{
    if (Menu && IsLocalController() && !Menu->IsInViewport())//c'è l'errore nel check e sparisce se sono fullscreen
    {
        Menu->AddToViewport();
        SetIModeUI();
    }
}



void APuzzlePlatformPlayerController::SetIModeUI()
{       
    if (IsLocalController())
    { 
        FInputModeUIOnly InputModeData;
        InputModeData.SetWidgetToFocus(Menu->TakeWidget());
        InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        bShowMouseCursor = true;

        SetInputMode(InputModeData);    
    }
}

void APuzzlePlatformPlayerController::SetIModeGame()
{
    if (IsLocalController())
    { 
        FInputModeGameOnly InputModeData;
        SetInputMode(InputModeData);
        bShowMouseCursor = false;;
    }
}

//potrei fare switch camera
void APuzzlePlatformPlayerController::SetPawnCameraBehind()
{
    if (IsLocalController() && PawnCameras.Num() >= 2  )
    {
        for (auto& CameraComp : PawnCameras)
        {
            if (CameraComp->ComponentHasTag("BehindCamera"))
            {
                CameraComp->SetActive(true);
            }
  
            if (CameraComp->ComponentHasTag("SetupCamera"))
            {
                CameraComp->SetActive(false);
            }
          
        }
        /*
        //non mi piace
        //camera behind
        PawnCameras[0]->SetActive(true);
        //camera setup
        PawnCameras[1]->SetActive(false);
        */
    }
}

void APuzzlePlatformPlayerController::SetPawnCameraSetup()
{
    if (IsLocalController() && PawnCameras.Num() >= 2)
    {
        for (auto& CameraComp : PawnCameras)
        {
            if (CameraComp->ComponentHasTag("BehindCamera"))
            {
                CameraComp->SetActive(false);
            }

            if (CameraComp->ComponentHasTag("SetupCamera"))
            {
                CameraComp->SetActive(true);
            }

        }
        /*
        //camera behind
        PawnCameras[0]->SetActive(false);
        //camera setup
        PawnCameras[1]->SetActive(true);
        */
    }
}


