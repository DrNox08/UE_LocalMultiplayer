#include "Public/Game/ElevatorSwitch.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Public/Game/ElevatorPlatform.h"


AElevatorSwitch::AElevatorSwitch()
{
	PrimaryActorTick.bCanEverTick = false;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetGenerateOverlapEvents(true);
}


void AElevatorSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AElevatorSwitch::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AElevatorSwitch::OnEndOverlap);
}


void AElevatorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AElevatorSwitch::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;
	
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character) return;
	
	OccupantCount++;
	
	if (OccupantCount == 1)
	{
		for (AElevatorPlatform* Elevator : LinkedElevators)
		{
			if (Elevator)
			{
				Elevator->SetActivated(true);
			}
		}
	}
}

void AElevatorSwitch::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority()) return;
	
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character) return;
	
	OccupantCount = FMath::Max(0, OccupantCount - 1);
	
	if (OccupantCount == 0)
	{
		for (AElevatorPlatform* Elevator : LinkedElevators)
		{
			if (Elevator)
			{
				Elevator->SetActivated(false);
			}
		}
	}
}
