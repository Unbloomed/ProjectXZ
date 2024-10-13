#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Item/XZItemBase.h"
#include "XZAttachment.generated.h"

class UXZDA_Weapon;

UCLASS()
class PROJECTXZ_API AXZAttachment : public AXZItemBase
{
	GENERATED_BODY()
	
public:	
	AXZAttachment();
	USkeletalMeshComponent* GetWeaponMesh() { return ItemMesh; }

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Properties")
	FGameplayTag WeaponNameTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Data Asset")
	TObjectPtr<UXZDA_Weapon> DA_Weapon;
};
