// Copyright Darren Temple

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTimeSeconds) override;
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnPossessedTankDeath();

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 8000.0;
};
