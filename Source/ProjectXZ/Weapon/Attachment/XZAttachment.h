#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Item/XZItemBase.h"
#include "Interface/ICombat.h"
#include "XZAttachment.generated.h"

UCLASS()
class PROJECTXZ_API AXZAttachment : public AXZItemBase, public IICombat
{
	GENERATED_BODY()
	
public:	
	AXZAttachment();
	TObjectPtr<USkeletalMeshComponent> GetWeaponMesh() { return ItemMesh; }

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Properties")
	FGameplayTag WeaponNameTag;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Fire(const FVector_NetQuantize& HitLocation, const FName& MuzzleSocketName) override;
	
	UFUNCTION(Server, Reliable)
	void Server_Fire(const FVector_NetQuantize& HitLocation, const FTransform& SocketTransform);
	
};
