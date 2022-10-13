// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()


protected:

	virtual void NativeOnInitialized() override;

private:
	//Canvas
	UPROPERTY(meta = ( BindWidget ))
	class UImage* BackgroundImage;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	//MenuSwitcher
	UPROPERTY(meta = ( BindWidget ))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	//Main Menu
	UPROPERTY(meta = (BindWidget))
	class UButton* HostServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CarSetupMenuButton;

	UPROPERTY(meta = ( BindWidget ))
	class UButton* ResumeGameButton;

	//Join Menu
	UPROPERTY(meta = ( BindWidget ))
	class UEditableTextBox* IpAddressTextBox;

	UPROPERTY(meta = ( BindWidget ))
	class UButton* JoinServerButton;

	UPROPERTY(meta = ( BindWidget ))
	class UButton* CancelButton;

	//Car Setup Menu
	UPROPERTY(meta = ( BindWidget ))
	class UWidget* CarSetupMenu;

	UPROPERTY(meta = ( BindWidget ))
	class USpinBox* RedSlide;

	UPROPERTY(meta = ( BindWidget ))
	class USpinBox* GreenSlide;

	UPROPERTY(meta = ( BindWidget ))
	class USpinBox* BlueSlide;

	UPROPERTY(meta = (BindWidget))
	class UButton* ChangeCarBodyColorButton;

	UPROPERTY(meta = ( BindWidget ))
	class UButton* CancelButton1;
	
	
	//buttons-functions binding
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void GoToMainMenu();

	UFUNCTION()
	void CloseMainMenu();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenCarSetupMenu();

	UFUNCTION()
	void ChangeCarBodyColor();

};
