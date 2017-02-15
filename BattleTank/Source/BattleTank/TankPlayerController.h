// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	virtual void Tick( float DeltaTime ) override; // Optional having the named input
	virtual void BeginPlay() override;
	bool GetSightRay(FVector& HitLocation) const; // Return an OUT parameter, true if crosshair hits landscape
};
