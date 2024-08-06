#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectXZ/Weapon/WeaponLibrary.h"
#include "XZProjectile.generated.h"

class USoundCue;
class UBoxComponent;
class UProjectileMovementComponent;

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
