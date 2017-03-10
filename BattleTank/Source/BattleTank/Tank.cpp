// Copyright Darren Temple

#include "BattleTank.h"
#include "Tank.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount,
				 struct FDamageEvent const & DamageEvent,
				 class AController * EventInstigator,
				 AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	return DamageToApply;
}
