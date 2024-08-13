#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "WeaponLibrary.generated.h"

/**
 * 
 */

class AXZAttachment;
class UTimelineComponent;
class AXZProjectile;

USTRUCT()
struct FWeaponListData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag WeaponTag;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AXZAttachment> WeaponActor;
};

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
struct FCameraZoomData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float TargetArmLength = 200.0f;

	UPROPERTY(EditAnywhere)
	FVector SocketOffset;

	UPROPERTY(EditAnywhere)
	float FieldOfView = 90.0f;

	UPROPERTY(EditAnywhere)
	bool bEnableCameraLag = true;
};

USTRUCT()
struct FAimData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCurveFloat> AimCurve;

	UPROPERTY(EditDefaultsOnly)
	FCameraZoomData BaseZoomData; // Zoom X

	UPROPERTY(EditDefaultsOnly)
	FCameraZoomData WeaponZoomData; // Zoom O

	UPROPERTY(EditDefaultsOnly)
	float AimingSpeed = 200.0f;
};

USTRUCT()
struct FActionData 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* ActionMontage; // ?꾪닾 紐쏀?二?諛쒖궗, ?④? 怨듦꺽 ??

	UPROPERTY(EditDefaultsOnly)
	float Action_FrameTime = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimationAsset> GunFireAnimation;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocketName = TEXT("MuzzleFlash");

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> MuzzleFlashEffect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

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
	uint32 Ammo = 10; // ?꾩옱 諛쒖궗?????덈뒗 珥앹븣 ??

	UPROPERTY(EditDefaultsOnly)
	uint32 MagCapacity = 10; // ???꾩갹???댁쓣 ???덈뒗 理쒕? 珥앹븣 ??

	UPROPERTY(EditDefaultsOnly)
	uint32 TotalAmmo = 30; // (?꾩옱 諛쒖궗 媛?ν븳 珥앹븣???쒖쇅?? ?꾩껜 珥앹븣 ??

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;
};

USTRUCT()
struct FProjectileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float InitialSpeed = 15000.0f; // ProjectileBullet(=珥앹븣) ?띾룄

	UPROPERTY(EditDefaultsOnly)
	float GravityScale = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ImpactBlood; // 異⑸룎 ?????源

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ImpactParticles; // 異⑸룎 ???뚰떚??

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> ImpactSound;  // 異⑸룎 ???ъ슫??
};
