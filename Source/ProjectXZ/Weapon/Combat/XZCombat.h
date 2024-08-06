#pragma once
#include "CoreMinimal.h"
#include "ProjectXZ/Weapon/WeaponLibrary.h"
#include "XZCombat.generated.h"

class AXZProjectile;
class AXZMagazine;

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

	void FireAction(const FVector_NetQuantize& HitTaget);
	void ReloadAction();


private:
	void OnFireBullet(const FVector_NetQuantize& HitTargettLocation);
	void OnEjectMagazine();
	void OnThrowMagazineToGround();
	void OnAttachNewMagazine();

	TObjectPtr<AXZAttachment> XZAttachment;
	ACharacter* OwnerCharacter;
	TArray<FActionData> ActionDatas;
	FBulletData BulletData;

	uint32 Idx = 0;

	TObjectPtr<AXZProjectile> SpawnedProjectile;
	TObjectPtr<AXZMagazine> EjectedMagazine;
	TObjectPtr<AXZMagazine> NewMagazine;
	
};
