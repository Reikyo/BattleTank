// Copyright Darren Temple

#include "BattleTank.h"
#include "Tank.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartHealth;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartHealth;
}

float ATank::TakeDamage(float DamageAmount,
				 struct FDamageEvent const & DamageEvent,
				 class AController * EventInstigator,
				 AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}
