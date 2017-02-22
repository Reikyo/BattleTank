// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


// Hide categories from the Blueprint "Details" tab by e.g.:
UCLASS(meta=(BlueprintSpawnableComponent))//, hidecategories=("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
// -1 is max downward movement, +1 is max upward movement
	void Elevate(float RelativeSpeed);

private:
// The "Category" field provides the Blueprint location in the "Details" tab
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5.0;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.0;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40.0;
};
