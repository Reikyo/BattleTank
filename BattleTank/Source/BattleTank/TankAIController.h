// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

private:
//	AActor PlayerPawn;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	void AimTowardsPlayer();
};