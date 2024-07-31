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
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimationAsset> GunFireAnimation;
	
	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocketName = TEXT("MuzzleFlash");

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AXZProjectile> ProjectileClass;
};

USTRUCT()
struct FBulletData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> CasingClass;

	UPROPERTY(EditDefaultsOnly)
	FName CasingSocketName = TEXT("CasingSocket");

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> ReloadMontage;

	UPROPERTY(EditDefaultsOnly)
	float EjectMagazine_FrameTime = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float ThrowMagazine_FrameTime = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float AttachMagazine_FrameTime = 0.8f;

	UPROPERTY(EditDefaultsOnly)
	FName MagazineSocketName = TEXT("MagazineSocket");

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AXZProjectile> ProjectileClass;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> MagazineClass;

	UPROPERTY(EditDefaultsOnly)
	uint32 Ammo = 10; // 현재 발사할 수 있는 총알 수

	UPROPERTY(EditDefaultsOnly)
	uint32 MagCapacity = 10; // 한 탄창에 담을 수 있는 최대 총알 수

	UPROPERTY(EditDefaultsOnly)
	uint32 TotalAmmo = 30; // (현재 발사 가능한 총알을 제외한) 전체 총알 수

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;
};

USTRUCT()
struct FProjectileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float InitialSpeed = 15000.0f; // ProjectileBullet(=총알) 속도

	UPROPERTY(EditDefaultsOnly)
	float GravityScale = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ImpactBlood; // 충돌 후 피 튀김

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ImpactParticles; // 충돌 후 파티클

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> ImpactSound;  // 충돌 후 사운드
};
