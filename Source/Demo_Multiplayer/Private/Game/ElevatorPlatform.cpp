#include "Public/Game/ElevatorPlatform.h"

#include "Net/UnrealNetwork.h"


AElevatorPlatform::AElevatorPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(false);

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);
	
}


void AElevatorPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}


void AElevatorPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TargetLocation = bActivated ? StartLocation + FVector(0.f, 0.f, ElevatorHeight) : StartLocation;

	FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaTime, ElevatorSpeed);
	SetActorLocation(NewLocation);
}

void AElevatorPlatform::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AElevatorPlatform, bActivated);
}

void AElevatorPlatform::SetActivated(bool bNewActivated)
{
	if (HasAuthority())
	{
		bActivated = bNewActivated;
	}
}
