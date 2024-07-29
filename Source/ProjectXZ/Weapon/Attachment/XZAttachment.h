#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "XZAttachment.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class PROJECTXZ_API AXZAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	AXZAttachment();
	TObjectPtr<USkeletalMeshComponent> GetWeaponMesh() { return WeaponMesh; }

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditDefaultsOnly)
	FGameplayTag WeaponNameTag;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	TObjectPtr<USphereComponent> SphereCollision;

private:
	void ShowPickupWidget(bool bShow);

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties", meta = (AllowPrivateAccess = true))
	//TObjectPtr<UWidgetComponent> PickupWidget; //무기줍기 Widget
};
