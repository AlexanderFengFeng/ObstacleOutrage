// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "VT/VirtualTextureBuildSettings.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	//FString MyString = "My String Value";
	//UE_LOG(LogTemp, Display, TEXT("Configured Move Distance: %s"), *MyString);
}

// Called every frame
void AMovingPlatform::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
    MovePlatform(DeltaTime);
    RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(const float DeltaTime)
{

    if (ShouldPlatformReturn())
    {
        StartLocation = StartLocation
            + (PlatformVelocity.GetSafeNormal() * MoveDistance);
        SetActorLocation(StartLocation);
        PlatformVelocity = -PlatformVelocity;
    }
    else
    {
        FVector CurrentLocation = GetActorLocation();
        CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
        SetActorLocation(CurrentLocation);
    }
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
    return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
    return FVector::Dist(StartLocation, GetActorLocation());
}


void AMovingPlatform::RotatePlatform(const float DeltaTime)
{
    SetActorRotation(GetActorRotation() + PlatformRotation * DeltaTime);
}