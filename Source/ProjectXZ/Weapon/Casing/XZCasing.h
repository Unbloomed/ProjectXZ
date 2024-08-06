#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XZCasing.generated.h"

/*  class	: ź�� Actor Ŭ����
 *  ���		: �Ѿ��� �߻�Ǹ� �ѿ��� ź�ǰ� ���� �� ������Ű�� ���ʹ�.
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
	float ShellEjectionImpulse; // �Ѿ�ź�ǰ� ������ �ӵ���
};
