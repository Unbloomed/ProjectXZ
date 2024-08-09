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

	FORCEINLINE const TArray<FActionData>& GetActionData() { return ActionDatas; }
	FORCEINLINE FBulletData& GetBulletData() { return BulletData; }

	void ConsumeAmmo();

	void FireAction(const FVector_NetQuantize& HitTaget, const FTransform& SocketTransform);
	void ReloadAction(const FTransform& SocketTransform);


private:
	void OnFireBullet(const FVector_NetQuantize& HitTargetLocation, const FTransform& SocketTransform);
	void OnEjectMagazine(const FTransform& SocketTransform);
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
