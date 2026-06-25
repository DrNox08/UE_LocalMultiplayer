#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorSwitch.generated.h"

class AElevatorPlatform;
class UBoxComponent;

UCLASS()
class DEMO_MULTIPLAYER_API AElevatorSwitch : public AActor
{
	GENERATED_BODY()

public:
	AElevatorSwitch();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	// Assegno da editor
	UPROPERTY(EditInstanceOnly, Category="Elevator")
	TArray<AElevatorPlatform*> LinkedElevators;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                    bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
	
	int32 OccupantCount = 0;
};
