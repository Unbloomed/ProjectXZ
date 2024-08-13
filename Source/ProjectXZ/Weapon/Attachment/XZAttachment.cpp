#include "XZAttachment.h"
#include "Components/SphereComponent.h"

AXZAttachment::AXZAttachment()
{
	//PrimaryActorTick.bCanEverTick = false;
	SetReplicateMovement(true);
}

void AXZAttachment::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}
