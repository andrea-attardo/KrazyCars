// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

UCLASS()
class PUZZLEPLATFORM_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UFUNCTION(Server, Unreliable)
	void MoveForward(float Value);

	UFUNCTION(Server, Unreliable)
	void MoveRight(float Value);

public:
	UFUNCTION()
	void ChangeColorBodyCarMaterial(const FLinearColor&  NewRGBValue);

private:
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMeshComp;

	USkeletalMesh* CarSkeletalMeshRef;

	UMaterial* BodyCarMaterialRef;

	UPROPERTY(EditAnywhere, Category= "Material Instance")
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraBehindComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraSetupComp;

	UPROPERTY(EditAnywhere)
	float Speed;

	FVector Velocity;

	float TurnRate;

};
