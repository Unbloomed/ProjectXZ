#pragma once
#include "CoreMinimal.h"
#include "ProjectXZ/Weapon/WeaponLibrary.h"
#include "XZCombat.generated.h"

class AXZProjectile;
/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZCombat : public UObject
{
	GENERATED_BODY()

public:
	void Init(class AXZAttachment* InWeapon, ACharacter* InOwner, const TArray<FActionData>& InData);
	void FireAction(const FVector& HitTaget);

private:
	void OnFireBullet();

	TObjectPtr<AXZAttachment> XZAttachment;
	ACharacter* OwnerCharacter;
	TArray<FActionData> ActionDatas;

	uint32 Idx = 0;

	TObjectPtr<AXZProjectile> SpawnedProjectile;

	FVector HitTargetLocation;
};
