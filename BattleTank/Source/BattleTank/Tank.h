// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
// The following "BlueprintCallable" methods will be available for the Tank_BP Blueprint associated with this Tank class i.e. they will be available as nodes
	UFUNCTION(BlueprintCallable, Category = Setup) // Don't put a semicolon after a UFUNCTION declaration!
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeSeconds = 3.0;
	double LastFireTime = 0.0;
//	UPROPERTY(EditDefaultsOnly, Category = Setup)
//	UClass* ProjectileBlueprint = nullptr; // Chose NOT to use this way of defining this variable here, as it lets the designer choose any class at all within Blueprint, which is too much choice and can lead to crashes if the wrong class is chosen
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;
// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	ATank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;
};
