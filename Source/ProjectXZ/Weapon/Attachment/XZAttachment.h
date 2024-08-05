#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Item/XZItemBase.h"
#include "XZAttachment.generated.h"

UCLASS()
class PROJECTXZ_API AXZAttachment : public AXZItemBase
{
	GENERATED_BODY()
	
public:	
	AXZAttachment();
	TObjectPtr<USkeletalMeshComponent> GetWeaponMesh() { return ItemMesh; }

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Properties")
	FGameplayTag WeaponNameTag;

protected:
	virtual void BeginPlay() override;


};
