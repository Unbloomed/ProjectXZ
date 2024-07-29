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
	void Init(class AXZAttachment* InWeapon, ACharacter* InOwner, const TArray<FActionData>& InActionDatas, const FBulletData& InBulletData);

	FORCEINLINE FBulletData& GetBulletData() { return BulletData; }
	FORCEINLINE void ConsumeAmmo() { BulletData.Ammo--; }

	void FireAction(const FVector& HitTaget);
	void ReloadAction();


private:
	void OnFireBullet(const FVector& HitTargettLocation);
	void OnRemoveMagazine();
	void OnAttachNewMagazine();

	TObjectPtr<AXZAttachment> XZAttachment;
	ACharacter* OwnerCharacter;
	TArray<FActionData> ActionDatas;
	FBulletData BulletData;

	uint32 Idx = 0;

	TObjectPtr<AXZProjectile> SpawnedProjectile;
	TObjectPtr<AActor> SpawnedMagazine;
	
};
