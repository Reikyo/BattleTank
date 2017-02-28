// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::IntendMoveForwards(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw)
}

void UTankMovementComponent::IntendMoveBackwards(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw)
}
