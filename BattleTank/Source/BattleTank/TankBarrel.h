// Copyright Darren Temple

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
// -1 is max downward movement, +1 is max upward movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 5.0;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = 0.0;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 40.0;
};
