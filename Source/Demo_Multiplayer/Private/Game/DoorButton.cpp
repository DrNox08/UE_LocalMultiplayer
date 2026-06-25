#include "Public/Game/DoorButton.h"

#include "Net/UnrealNetwork.h"
#include "Public/Game/DoorActor.h"


ADoorButton::ADoorButton()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(RootComponent);
}

void ADoorButton::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADoorButton, bIsToggled);
}

void ADoorButton::BeginPlay()
{
	Super::BeginPlay();
	UpdateMaterial();
}


void ADoorButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoorButton::OnRep_IsToggled()
{
	UpdateMaterial();
}

void ADoorButton::Interact(AActor* Caller)
{
	if (!HasAuthority()) return;
	
	bIsToggled = !bIsToggled;
	UpdateMaterial();

	for (ADoorActor* Door : LinkedDoors)
	{
		if (Door)
		{
			Door->ToggleDoor();
		}
	}
}

void ADoorButton::UpdateMaterial()
{
	if (ButtonMesh)
	{
		ButtonMesh->SetMaterial(0, bIsToggled ? MaterialDoorOpen : MaterialDoorClosed);
	}
}


