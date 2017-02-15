// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()))
	}
}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; // Out parameter
	if (GetSightRay(HitLocation)) // Has the "side effect" of causing a line trace
	{
//		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()))
	}
}

// Get world location of linetrace through crosshair, true if hits the landscape
bool ATankPlayerController::GetSightRay(FVector& HitLocation) const
{
	// Find the crosshair position in (x,y) screen pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// Find the crosshair look direction in normalised (x,y,z) game world coordinates
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(LookDirection.ToString()))
	}

//	HitLocation = FVector(1.0);
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X,
										  ScreenLocation.Y,
										  CameraWorldLocation,
										  LookDirection);
}
