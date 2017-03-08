// Copyright Darren Temple

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
// Find the sideways slippage speed and the force required to bring the slippage speed to zero in DeltaTime. Note that this code will run once per track, so the applied force with each method call is half of the total required.
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto CorrectionAcceleration = -1.0 * (SlippageSpeed / DeltaTime) * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>GetOwner()->GetRootComponent();
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration;
	TankRoot->AddForce(CorrectionForce / 2.0);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // GetOwner() gets the Tank_BP, then GetRootComponent() gets the Tank body to which everything else is attached
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
