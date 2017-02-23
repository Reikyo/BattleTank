// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"


// Hide categories from the Blueprint "Details" tab by e.g.:
UCLASS(meta=(BlueprintSpawnableComponent))//, hidecategories=("Collision"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
// -1 is max ??? movement, +1 is max ??? movement
	void Rotate(float RelativeSpeed);
	
private:
// The "Category" field provides the Blueprint location in the "Details" tab
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 20.0;
};
