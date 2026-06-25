#include "Public/Game/WinTriggerBox.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Public/Game/CoopGameMode.h"


AWinTriggerBox::AWinTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetGenerateOverlapEvents(true);
}


void AWinTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWinTriggerBox::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AWinTriggerBox::OnEndOverlap);

	if (HasAuthority())
	{
		ACoopGameMode* GM = Cast<ACoopGameMode>(GetWorld()->GetAuthGameMode());
		UE_LOG(LogTemp, Warning, TEXT("WinTrigger BeginPlay - GameMode cast: %s"), GM ? TEXT("OK") : TEXT("FAILED"));
		if (GM)
		{
			GM->RegisterWinTrigger(this);
		}
	}
}


void AWinTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWinTriggerBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character) return;

	bOccupied = true;

	if (ACoopGameMode* GM = Cast<ACoopGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnTriggerStateChanged();
	}
}

void AWinTriggerBox::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority()) return;

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character) return;

	bOccupied = false;
}
