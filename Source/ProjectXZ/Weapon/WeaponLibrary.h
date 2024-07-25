#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponLibrary.generated.h"

/**
 * 
 */

class AXZProjectile;
USTRUCT()
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> UnequipMontage;

	UPROPERTY(EditDefaultsOnly)
	float Equip_FrameTime = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float Unequip_FrameTime = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	FName HolsterSocketName;

	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocketName;
};

USTRUCT()
struct FActionData 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* ActionMontage; // 전투 몽타주(발사, 단검 공격 등)

	UPROPERTY(EditDefaultsOnly)
	float Action_FrameTime = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocketName = TEXT("MuzzleFlash");

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AXZProjectile> ProjectileClass;
};
