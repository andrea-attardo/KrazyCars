// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "DrawDebugHelpers.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);   

    Speed = 100.f;
    bIsActive = true;
    
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    { 
      SetReplicates(true);
      SetReplicateMovement(true);
    }

    GlobalTargetLocation = GetTransform().TransformPosition(LocalTargetLocation);
    GlobalStartLocation = GetActorLocation();
    PathLength = ( GlobalTargetLocation - GlobalStartLocation ).Size();

    //UE_LOG(LogTemp, Warning, TEXT("ACTOR: %s | LOC_ROLE: %d | REM_ROLE %d "), *GetName(), GetLocalRole(), GetRemoteRole());    

}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    { 
        if (bIsActive) MoveBackForth(DeltaTime);
        
    }
}


void AMovingPlatform::MoveBackForth(float DeltaTime)
{
    FVector CurrentActorLocation = GetActorLocation();
    float PathTravelled = ( CurrentActorLocation - GlobalStartLocation ).Size();

    if (PathTravelled >= PathLength)
    {
        FVector Temp = GlobalTargetLocation;
        GlobalTargetLocation = GlobalStartLocation;
        GlobalStartLocation = Temp;
    }

    FVector Direction = ( GlobalTargetLocation - CurrentActorLocation ).GetSafeNormal();

    FVector NewLocation = CurrentActorLocation + ( Direction * Speed * DeltaTime );

    DrawDebugLine(GetWorld(), FVector(0.f, 0.f, 300.f), FVector(0.f, 0.f, 300.f) + Direction * Speed, FColor::Red);

    SetActorLocation(NewLocation);
}
