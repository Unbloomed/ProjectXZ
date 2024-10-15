#include "TriggerBox/CameraEventTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Components/ShapeComponent.h"
#include "Character/XZCharacter.h"

ACameraEventTriggerBox::ACameraEventTriggerBox()
{
	GetCollisionComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCollisionComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACameraEventTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionComponent()->SetSimulatePhysics(true);
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACameraEventTriggerBox::OnActorBeginOverlap);
}

void ACameraEventTriggerBox::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("[ACameraEventTriggerBox] OnActorBeginOverlap"));

	if ( this == OtherActor)
	{
		return;
	}
	
	if ( APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)  )
	{
		UE_LOG(LogTemp, Log, TEXT("[ACameraEventTriggerBox] SetViewTargetWithBlend"));
		PlayerController->SetViewTargetWithBlend(Camera);
	}
}
