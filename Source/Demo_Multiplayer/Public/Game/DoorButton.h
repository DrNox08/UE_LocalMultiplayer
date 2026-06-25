#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/Interactable.h"
#include "DoorButton.generated.h"

class ADoorActor;

UCLASS()
class DEMO_MULTIPLAYER_API ADoorButton : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ADoorButton();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Interact(AActor* Caller) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ButtonMesh;
	
	UPROPERTY(EditInstanceOnly, Category = "Door")
	TArray<ADoorActor*> LinkedDoors;

	UPROPERTY(EditAnywhere, Category = "Door")
	UMaterialInterface* MaterialDoorClosed;

	UPROPERTY(EditAnywhere, Category = "Door")
	UMaterialInterface* MaterialDoorOpen;
	
	UPROPERTY(ReplicatedUsing = OnRep_IsToggled)
	bool bIsToggled = false;

	UFUNCTION()
	void OnRep_IsToggled();
	
private:
	
	void UpdateMaterial();
};
