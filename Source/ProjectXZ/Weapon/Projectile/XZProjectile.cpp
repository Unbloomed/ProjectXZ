#include "XZProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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

	if (HasAuthority())
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	}

}

// 내장함수 Destroyed()는 Destroy()함수가 호출된 후 호출된다.
void AXZProjectile::Destroyed()
{
	Super::Destroyed();

}

void AXZProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ACharacter* HittedCharacter = Cast<ACharacter>(Hit.GetActor());
	if (IsValid(HittedCharacter))
	{
		// TODO: 피 튀기기 효과 + 사운드
	}
	else
	{
		// 총알 바닥/벽에 닿는 순간 효과 + 사운드
		if (ProjectileData.ImpactParticles)
		{	
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ProjectileData.ImpactParticles, GetActorTransform());
		}
		if (ProjectileData.ImpactSound)
		{
			//UGameplayStatics::PlaySoundAtLocation(this, ProjectileData.ImpactSound, GetActorLocation());
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
