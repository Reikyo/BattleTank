// Copyright Darren Temple

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTimeSeconds)
{
	Super::Tick(DeltaTimeSeconds);

	auto AIPawn = GetPawn();
	if (!ensure(AIPawn)) { return; }
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerPawn)) { return; }
	auto AimingComponent = AIPawn->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	MoveToActor(PlayerPawn, AcceptanceRadius);
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}
