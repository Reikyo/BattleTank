// Copyright Darren Temple

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
// The following is called whenever the track is hit. Requires "Simulation Generates Hit Events" to be checked in the track component of the tank Blueprint.
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0;
}

void UTankTrack::ApplySidewaysForce()
{
// Find the sideways slippage speed and the force required to bring the slippage speed to zero in DeltaTime. Note that this code will run once per track, so the applied force with each method call is half of the total required.
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto DeltaTime = GetWorld()->GetTimeSeconds();
	auto CorrectionAcceleration = -1.0 * (SlippageSpeed / DeltaTime) * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration;
	TankRoot->AddForce(CorrectionForce / 2.0);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0, 1.0);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // GetOwner() gets the Tank_BP, then GetRootComponent() gets the Tank body to which everything else is attached
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
