// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:	
	UPuzzlePlatformGameInstance();

public:
	

protected:
	virtual void Init() override;

public:
	UFUNCTION(exec)
	void Host();

	UFUNCTION(exec)
	void Join(const FString& IPAddress);


};
