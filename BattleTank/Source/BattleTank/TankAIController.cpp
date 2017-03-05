// Copyright Darren Temple

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTimeSeconds)
{
	Super::Tick(DeltaTimeSeconds);

	auto AIPawn = Cast<ATank>(GetPawn());
	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(AIPawn && PlayerPawn))
	{
		MoveToActor(PlayerPawn, 3000.0);
		AIPawn->AimAt(PlayerPawn->GetActorLocation());
		AIPawn->Fire();
	}
}
