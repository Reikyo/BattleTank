// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Setup) // Don't put a semicolon after a UFUNCTION declaration!
	void SetBarrelReference(UTankBarrel* BarrelToSet);

private:
	UPROPERTY(EditAnywhere)
	float LaunchSpeed = 100000.0;

	ATank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
};
