// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the turret the right amount this frame given a max rotation speed and the frame time
	auto RelativeSpeedClamp = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	auto RotationChange = RelativeSpeedClamp * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
//	UE_LOG(LogTemp, Warning, TEXT("RelativeRotation.Yaw: %f RotationChange: %f RawNewRotation: %f"), RelativeRotation.Yaw, RotationChange, RawNewRotation)
	SetRelativeRotation(FRotator(0.0, RawNewRotation, 0.0));
}
