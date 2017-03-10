// Copyright Darren Temple

#include "BattleTank.h"
#include "Projectile.h"

// Note that we do not need to create a "ProjectileMovementComponent" C++ class, as we had to do for the similar addition of "TankAimingComponent" in the Tank codes, as "ProjectileMovementComponent" is an existing Unreal class


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
 	SetRootComponent(CollisionMesh);
 	CollisionMesh->SetNotifyRigidBodyCollision(true);
 	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
	return;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
}
