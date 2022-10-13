// Fill out your copyright notice in the Description page of Project Settings.


#include "PatformTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MovingPlatform.h"

// Sets default values
APatformTrigger::APatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerVolumeComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume Component"));
	RootComponent = TriggerVolumeComponent;

	PressurePadComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	PressurePadComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		TriggerVolumeComponent->OnComponentBeginOverlap.AddDynamic(this, &APatformTrigger::OnOverlapBegin);
		TriggerVolumeComponent->OnComponentEndOverlap.AddDynamic(this, &APatformTrigger::OnOverlapEnd);

		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AMovingPlatform::StaticClass(), FName("PlatformA"), Platforms);
	}

	
}

// Called every frame
void APatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// UE_LOG(LogTemp, Warning, TEXT("Activated"));
	 
	for (auto& Platform : Platforms)
	 {
		 Cast<AMovingPlatform>(Platform)->SetActive(false);
	 }

}

void APatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Deactivated"));

	for (auto& Platform : Platforms)
	{
		Cast<AMovingPlatform>(Platform)->SetActive(true);
	}
}

