// Copyright Darren Temple

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount,
							 struct FDamageEvent const & DamageEvent,
							 class AController * EventInstigator,
							 AActor * DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartHealth;

	ATank();
};
