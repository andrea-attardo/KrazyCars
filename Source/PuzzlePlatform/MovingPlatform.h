// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetActive(bool NewValue) { bIsActive = NewValue; }

private:
	
	bool bIsActive;

	void MoveBackForth(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere, Meta = ( MakeEditWidget = true ))
	FVector LocalTargetLocation;
	
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	float PathLength;

};
