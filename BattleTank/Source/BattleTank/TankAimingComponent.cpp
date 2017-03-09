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
	if (AmmoCount == 0)
	{
		FiringState = EFiringState::AmmoGone;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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
	if (FMath::Abs(DeltaRotator.Yaw) < 180.0)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else if (DeltaRotator.Yaw > 180.0)
	{
		Turret->Rotate(DeltaRotator.Yaw - 360.0);
	}
	else if (DeltaRotator.Yaw < -180.0)
	{
		Turret->Rotate(DeltaRotator.Yaw + 360.0);
	}
	Barrel->Elevate(DeltaRotator.Pitch);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto ForwardVector = Barrel->GetForwardVector();
	auto bIsBarrelMoving = !ForwardVector.Equals(AimDirection, 0.01);
	return bIsBarrelMoving;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}

void UTankAimingComponent::Fire()
{
	if ((FiringState == EFiringState::Locked) || (FiringState == EFiringState::Aiming))
	{
		if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
							ProjectileBlueprint,
							Barrel->GetSocketLocation(FName("Projectile")),
							Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoCount -= 1;
	}
}
