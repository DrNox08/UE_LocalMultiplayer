#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorPlatform.generated.h"

UCLASS()
class DEMO_MULTIPLAYER_API AElevatorPlatform : public AActor
{
	GENERATED_BODY()

public:
	AElevatorPlatform();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void SetActivated(bool bNewActivated);

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(Replicated)
	bool bActivated = false;


	UPROPERTY(EditAnywhere, Category="Elevator")
	float ElevatorHeight = 500.f;

	UPROPERTY(EditAnywhere, Category="Elevator")
	float ElevatorSpeed = 200.f;

private:
	FVector StartLocation;
};
