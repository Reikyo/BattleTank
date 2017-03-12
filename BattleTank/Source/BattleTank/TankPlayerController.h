// Copyright Darren Temple

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;


// Responsible for helping the player aim
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTimeSeconds) override; // Optional having the named input
	void AimTowardsCrosshair();
	bool GetSightRay(FVector& HitLocation) const; // Return an OUT parameter, true if crosshair hits landscape
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnPossessedTankDeath();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);
};
