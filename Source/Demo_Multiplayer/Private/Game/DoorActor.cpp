// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Game/DoorActor.h"

#include "Net/UnrealNetwork.h"


ADoorActor::ADoorActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(false);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);
}

void ADoorActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ADoorActor, bIsOpen);
}

void ADoorActor::ToggleDoor()
{
	if (!HasAuthority()) return;
	
	bIsOpen = !bIsOpen;
}


void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	ClosedLocation = GetActorLocation();
}


void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector TargetLocation = bIsOpen
		? ClosedLocation - FVector(0.f, 500.f, 0.f)
		: ClosedLocation;

	FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaTime, DoorSpeed);
	SetActorLocation(NewLocation);
}
