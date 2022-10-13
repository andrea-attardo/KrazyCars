// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/SpinBox.h"
#include "PuzzlePlatformGameInstance.h"
#include "PuzzlePlatformPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Car.h"


void UMainMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (HostServerButton && JoinMenuButton && CancelButton && CancelButton1 && JoinServerButton && ResumeGameButton && CarSetupMenuButton && ChangeCarBodyColorButton)
    {
        HostServerButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
        JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
        CancelButton->OnClicked.AddDynamic(this, &UMainMenu::GoToMainMenu);
        CancelButton1->OnClicked.AddDynamic(this, &UMainMenu::GoToMainMenu);
        JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
        ResumeGameButton->OnClicked.AddDynamic(this, &UMainMenu::CloseMainMenu);
        CarSetupMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenCarSetupMenu);
        ChangeCarBodyColorButton->OnClicked.AddDynamic(this, &UMainMenu::ChangeCarBodyColor);
    }

}


void UMainMenu::HostServer()
{
    if (GetOwningPlayer()->HasAuthority())
    { 
        Cast<UPuzzlePlatformGameInstance>(GetGameInstance())->Host();
        Cast<APuzzlePlatformPlayerController>(GetOwningPlayer())->SetIModeGame();
    }
}

void UMainMenu::OpenJoinMenu()
{
    if (MenuSwitcher && JoinMenu)
    {
        MenuSwitcher->SetActiveWidget(JoinMenu);
    }
}


void UMainMenu::JoinServer()
{

    if (IpAddressTextBox)
    {
        FString IPAddress = IpAddressTextBox->GetText().ToString();

        Cast<UPuzzlePlatformGameInstance>(GetGameInstance())->Join(IPAddress);
        Cast<APuzzlePlatformPlayerController>(GetOwningPlayer())->SetIModeGame();
    }
    

}

void UMainMenu::OpenCarSetupMenu()
{
    Cast<APuzzlePlatformPlayerController>(GetOwningPlayer())->SetPawnCameraSetup();

    if (MenuSwitcher && BackgroundImage)
    {
        MenuSwitcher->SetActiveWidget(CarSetupMenu);
        BackgroundImage->SetOpacity(0.f);
    }
}


void UMainMenu::GoToMainMenu()
{
    if (MenuSwitcher && MainMenu)
    {
        MenuSwitcher->SetActiveWidget(MainMenu);
        BackgroundImage->SetOpacity(1.f);
    }

}

void UMainMenu::CloseMainMenu()
{ 
    Cast<APuzzlePlatformPlayerController>(GetOwningPlayer())->SetPawnCameraBehind();
    Cast<APuzzlePlatformPlayerController>(GetOwningPlayer())->SetIModeGame();
    RemoveFromViewport();
}



void UMainMenu::ChangeCarBodyColor()
{   
    //no good to directly modify material value
    if (RedSlide && GreenSlide && BlueSlide)
    {   
        
        FLinearColor NewRGBValue = FLinearColor(FMath::Floor(RedSlide->GetValue()), 
                                                FMath::Floor(GreenSlide->GetValue()),
                                                FMath::Floor(BlueSlide->GetValue()));
        Cast<ACar>(GetOwningPlayerPawn())->ChangeColorBodyCarMaterial(NewRGBValue);
    }
}