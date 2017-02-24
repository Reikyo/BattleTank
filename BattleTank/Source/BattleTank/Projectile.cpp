// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"

// Note that we do not need to create a "ProjectileMovementComponent" C++ class, as we had to do for the similar addition of "TankAimingComponent" in the Tank codes, as "ProjectileMovementComponent" is an existing Unreal class


// Sets default values
AProjectile::AProjectile()
{
// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTimeSeconds)
{
	Super::Tick(DeltaTimeSeconds);
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
	return;
}
