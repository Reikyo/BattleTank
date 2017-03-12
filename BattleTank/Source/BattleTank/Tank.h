// Copyright Darren Temple

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount,
							 struct FDamageEvent const & DamageEvent,
							 class AController * EventInstigator,
							 AActor * DamageCauser) override;
	FTankDelegate OnDeath;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialised in BeginPlay

	ATank();
	virtual void BeginPlay() override;
};
