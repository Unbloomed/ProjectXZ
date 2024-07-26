#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XZProjectile.generated.h"

class USoundCue;
class UBoxComponent;
class UProjectileMovementComponent;

USTRUCT()
struct FProjectileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float InitialSpeed = 15000.0f; // ProjectileBullet(=총알) 속도

	UPROPERTY(EditDefaultsOnly)
	float GravityScale = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ImpactBlood; // 충돌 후 피 튀김

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ImpactParticles; // 충돌 후 파티클

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> ImpactSound;  // 충돌 후 사운드
};

UCLASS()
class PROJECTXZ_API AXZProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AXZProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void StartDestroyTimer();
	void EndDestroyTimer();


	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Information")
	float DestroyTime = 3.0f; // 충돌하지 않았을때 소멸까지 걸리는 시간
	FTimerHandle DestroyTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Information")
	FProjectileData ProjectileData;
};
