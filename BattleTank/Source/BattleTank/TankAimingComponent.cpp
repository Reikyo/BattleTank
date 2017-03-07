// Copyright Darren Temple

#include "BattleTank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
}

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Turret) || !ensure(Barrel)) { return; }
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

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Turret) || !ensure(Barrel)) { return; }
// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
							ProjectileBlueprint,
							Barrel->GetSocketLocation(FName("Projectile")),
							Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}
