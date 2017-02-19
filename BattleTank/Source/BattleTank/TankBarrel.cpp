// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame given a max elevation speed and the frame time
	auto RelativeSpeedClamp = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	auto ElevationChange = RelativeSpeedClamp * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
// Note that "<float>" in the following is not essential, but it implicitly lets the method know what to expect and so removes the chance that some unwanted default behaviour occurs
	auto RawNewElevationClamp = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(RawNewElevationClamp, 0.0, 0.0));
}
