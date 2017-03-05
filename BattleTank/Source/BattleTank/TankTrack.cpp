// Copyright Darren Temple

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // GetOwner() gets the Tank_BP, then GetRootComponent() gets the Tank body to which everything else is attached
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
