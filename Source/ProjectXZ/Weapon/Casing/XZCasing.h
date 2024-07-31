#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XZCasing.generated.h"

/*  class	: 탄피 Actor 클래스
 *  사용		: 총알이 발사되면 총에서 탄피가 나갈 때 스폰시키는 액터다.
 */

UCLASS()
class PROJECTXZ_API AXZCasing : public AActor
{
	GENERATED_BODY()
	
public:	
	AXZCasing();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> CasingMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ShellSound; 

	UPROPERTY(EditAnywhere)
	float ShellEjectionImpulse; // 총알탄피가 나갈때 속도값
};
