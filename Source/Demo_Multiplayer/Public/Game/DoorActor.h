// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UCLASS()
class DEMO_MULTIPLAYER_API ADoorActor : public AActor
{
	GENERATED_BODY()

public:
	ADoorActor();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void ToggleDoor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(Replicated)
	bool bIsOpen = false;

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorSlideDistance = 300.f;

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorSpeed = 200.f;

private:
	FVector ClosedLocation;
};
