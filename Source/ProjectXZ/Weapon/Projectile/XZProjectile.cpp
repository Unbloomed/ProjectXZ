#include "XZProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

AXZProjectile::AXZProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetIsReplicated(true);
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->InitialSpeed = ProjectileData.InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileData.InitialSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = ProjectileData.GravityScale;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetIsReplicated(true);
}

void AXZProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovementComponent->InitialSpeed = ProjectileData.InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileData.InitialSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = ProjectileData.GravityScale;

	//if (HasAuthority())
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
		CollisionBox->IgnoreActorWhenMoving(Owner, true);
	}

	StartDestroyTimer();
}

void AXZProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ACharacter* HittedCharacter = Cast<ACharacter>(Hit.GetActor());
	if (IsValid(HittedCharacter) && ProjectileData.ImpactBlood)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ProjectileData.ImpactBlood, GetActorTransform());
	}
	else
	{
		// �Ѿ� �ٴ�/���� ��� ���� ȿ�� + ����
		if (ProjectileData.ImpactParticles)
		{	
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ProjectileData.ImpactParticles, GetActorTransform());
		}
		if (ProjectileData.ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ProjectileData.ImpactSound, GetActorLocation());
		}
	}

	Destroy();
}

void AXZProjectile::StartDestroyTimer()
{
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ThisClass::EndDestroyTimer, DestroyTime);
}

void AXZProjectile::EndDestroyTimer()
{
	Destroy();
}

// �����Լ� Destroyed()�� Destroy()�Լ��� ȣ��� �� ȣ��ȴ�.
void AXZProjectile::Destroyed()
{
	Super::Destroyed();

}
