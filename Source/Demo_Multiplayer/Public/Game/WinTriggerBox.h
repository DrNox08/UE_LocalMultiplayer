#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinTriggerBox.generated.h"

class UBoxComponent;

UCLASS()
class DEMO_MULTIPLAYER_API AWinTriggerBox : public AActor
{
	GENERATED_BODY()

public:

	AWinTriggerBox();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
public:
	
	bool IsOccupied() {return bOccupied;}	
	
private:
	
	bool bOccupied;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* TriggerMesh;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	
	
};
