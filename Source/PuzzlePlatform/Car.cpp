// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PuzzlePlatformPlayerController.h"
#include "MainMenu.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SkeletalMeshComp->SetIsReplicated(true);
	RootComponent = SkeletalMeshComp;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(SkeletalMeshComp);

	CameraBehindComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Behind Component"));
	CameraBehindComp->SetupAttachment(SpringArmComp);
	CameraBehindComp->ComponentTags.Add("CameraPawn");
	CameraBehindComp->ComponentTags.Add("BehindCamera");

	CameraSetupComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Setup Component"));
	CameraSetupComp->SetupAttachment(SkeletalMeshComp);
	CameraSetupComp->ComponentTags.Add("CameraPawn");
	CameraSetupComp->ComponentTags.Add("SetupCamera");

	//movement variables
	Velocity = FVector(1.f, 0.f, 0.f);
	Speed = 5000.f;
	TurnRate = 180.f;


	static  ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/Vehicle/Sedan/Materials/M_Vehicle_Sedan.M_Vehicle_Sedan'"));
	if (FoundMaterial.Succeeded())
	{
		BodyCarMaterialRef = FoundMaterial.Object;
	}

	/*
	//create materiale instance Body car
	static  ConstructorHelpers::FObjectFinder<USkeletalMesh> FoundMesh(TEXT("SkeletalMesh'/Game/Vehicle/Sedan/Sedan_SkelMesh.Sedan_SkelMesh'"));
	if (FoundMesh.Succeeded())
	{ 
		CarSkeletalMeshRef = FoundMesh.Object;
	}
	
	MaterialInstance = UMaterialInstanceDynamic::Create(BodyCarMaterialRef, CarSkeletalMeshRef);
	if (MaterialInstance)
	{ 
		TArray<FSkeletalMaterial> MeshMaterials = CarSkeletalMeshRef->GetMaterials();
		if(MeshMaterials.Num() <= 9)
		{ 
			MeshMaterials.Add(MaterialInstance);
			CarSkeletalMeshRef->SetMaterials(MeshMaterials);
		}
	}
	*/
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		bReplicates = true;
		SetReplicateMovement(true);
	}
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACar::MoveRight);
}

void ACar::MoveForward_Implementation(float Value)
{

	FVector DeltaLocation(0.f);
	DeltaLocation = Velocity * Speed * GetWorld()->GetDeltaSeconds() * Value;

	AddActorLocalOffset(DeltaLocation, true);
	
}

void ACar::MoveRight_Implementation(float Value)
{
	
	FRotator DeltaRotator(0.f);
	DeltaRotator.Yaw = TurnRate * GetWorld()->GetDeltaSeconds() * Value;

	AddActorLocalRotation(DeltaRotator, true);
	
}

void ACar::ChangeColorBodyCarMaterial(const FLinearColor&  NewRGBValue)
{
	if (IsLocallyControlled() && BodyCarMaterialRef)
	{ 
		
		//MaterialInstance->SetVectorParameterValue(FName(TEXT("Base Color")), NewRGBValue);
		BodyCarMaterialRef->SetVectorParameterValueEditorOnly(FName(TEXT("Base Color")), NewRGBValue);	
	}
}

