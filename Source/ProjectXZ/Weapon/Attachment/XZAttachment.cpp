#include "XZAttachment.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"

AXZAttachment::AXZAttachment()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	//PickupWidget->SetupAttachment(RootComponent);
}

void AXZAttachment::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	
}

void AXZAttachment::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (IsValid(Character))
	{
		ShowPickupWidget(true);
	}
}

void AXZAttachment::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (IsValid(Character))
	{
		ShowPickupWidget(false);
	}
}

void AXZAttachment::ShowPickupWidget(bool bShow)
{
	//if (PickupWidget)
	{
		//PickupWidget->SetVisibility(bShow);
	}
}
