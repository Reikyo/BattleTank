// Copyright Darren Temple

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


// TankTrack is used to set maximum driving force, and to apply forces to the tank
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDriveForce = 40000000.0; // Assuming 40tonne tank at 1g acceleration

// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

private:
	float CurrentThrottle = 0.0;
	UTankTrack();
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void ApplySidewaysForce();
	void DriveTrack();
};
