// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
//	auto OurTankName = GetOwner()->GetName();
//	auto BarrelLocation = Barrel->GetComponentLocation();
//	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *(HitLocation.ToString()), *(BarrelLocation.ToString()))
	if (!Barrel)
	{
		return;
	}
	if (!Turret)
	{
		return;
	}
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Look for the socket called "Projectile" that we added in the barrel Blueprint

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
								this,
								OutLaunchVelocity,
								StartLocation,
								HitLocation,
								LaunchSpeed,
								false,
								0.0,
								0.0,
								ESuggestProjVelocityTraceOption::DoNotTrace);
	auto Time = GetWorld()->GetTimeSeconds();
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
//		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time)
	}
	else
	{
//		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution not found"), Time)
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet)
	{
		return;
	}
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet)
	{
		return;
	}
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
//	UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *(DeltaRotator.ToString()))
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}
