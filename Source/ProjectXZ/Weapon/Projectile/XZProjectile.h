#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XZProjectile.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTXZ_API AXZProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AXZProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void StartDestroyTimer();
	void EndDestroyTimer();


	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(EditAnywhere)
	float InitialSpeed = 15000.0f; // ProjectileBullet(=총알) 속도

	UPROPERTY(EditAnywhere)
	float DestroyTime = 2.5f; // 충돌하지 않았을때 소멸까지 걸리는 시간
	FTimerHandle DestroyTimer;

};
