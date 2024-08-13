#include "XZAttachment.h"

#include "BaseGizmos/HitTargets.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"

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

void AXZAttachment::Fire(const FVector_NetQuantize& HitLocation, const FName& MuzzleSocketName)
{
	FTransform SocketTransform = GetWeaponMesh()->GetSocketByName(MuzzleSocketName)->GetSocketTransform(GetWeaponMesh());

}

void AXZAttachment::Server_Fire_Implementation(const FVector_NetQuantize& HitLocation, const FTransform& SocketTransform)
{
	
}
