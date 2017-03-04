// Copyright Darren Temple

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto AIForwardVectorNormalCurrent = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardVectorNormalIntend = MoveVelocity.GetSafeNormal();
	IntendMoveForwardsBackwards(FVector::DotProduct(AIForwardVectorNormalCurrent,
													AIForwardVectorNormalIntend));
	IntendMoveRight(FVector::CrossProduct(AIForwardVectorNormalCurrent,
										  AIForwardVectorNormalIntend).Z);
}

void UTankMovementComponent::IntendMoveForwardsBackwards(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveLeft(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
