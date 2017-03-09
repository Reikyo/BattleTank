// Copyright Darren Temple

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// Note that we do not need to create a "ProjectileMovementComponent" C++ class, as we had to do for the similar addition of "TankAimingComponent" in the Tank codes, as "ProjectileMovementComponent" is an existing Unreal class


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTimeSeconds) override;
	void LaunchProjectile(float Speed);

private:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;
};
