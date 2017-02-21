// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
// The following "BlueprintCallable" methods will be available for the Tank_BP Blueprint associated with this Tank class i.e. they will be available as nodes 
	UFUNCTION(BlueprintCallable, Category = Setup) // Don't put a semicolon after a UFUNCTION declaration!
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

private:
	UPROPERTY(EditAnywhere)
	float LaunchSpeed = 10000.0;

	ATank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
};
