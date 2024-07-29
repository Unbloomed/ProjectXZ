#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "XZWeaponComponent.generated.h"

class UXZWeaponData;
class UXZDA_Weapon;
class AXZCharacter;
class AXZPlayerController;
class AXZHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZWeaponComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TObjectPtr<AXZCharacter> GetXZCharacter();
	TObjectPtr<AXZPlayerController> GetXZPlayerController();
	TObjectPtr<AXZHUD> GetXZHUD();

	// 명령
	void EquipWeapon(const FGameplayTag& InTag);
	void Fire();
	void Reload(const FGameplayTag& InTag);
	void StartAiming();
	void EndAiming();

protected:
	virtual void BeginPlay() override;

private:
	void TraceUnderCrosshairs(FHitResult& TraceHitResult);
	void SetHUDCrosshairs(float InDeltaTime);
	void InterpFOV(float InDeltaTime);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Data", meta = (AllowPrivateAccess = true))
	TMap<FGameplayTag, UXZDA_Weapon*> WeaponList; // 전체 무기 목록(에디터에서 등록)

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Data", meta = (AllowPrivateAccess = true))
	TArray<FGameplayTag> Init_WeaponTags; // 시작 시 가지고 있는 무기

	UPROPERTY()
	TMap<FGameplayTag, UXZWeaponData*> Datas; // 현재 가지고 있는 무기들 데이터

	UPROPERTY()
	FGameplayTag EquippedWeaponTag = FXZTags::GetXZTags().Fist; // 현재 장착 중인 무기

	TObjectPtr<AXZCharacter> OwnerCharacter;
	FVector HitTarget; // 총알이 발사되서 충돌하게 될 지점

	//***************************************************************
	//** Crosshairs
	TObjectPtr<AXZHUD> XZHUD;
	TObjectPtr<AXZPlayerController> XZPlayerController;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> CrosshairTexture2D;
	//***************************************************************

	//***************************************************************
	//** Aiming
	bool bIsAiming = false;

	float CurrentFOV = 90.0f; // 현재 FOV 값
	UPROPERTY(EditDefaultsOnly, Category = "Aiming Data", meta = (AllowPrivateAccess = true))
	float ZoomedFOV = 30.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming Data", meta = (AllowPrivateAccess = true))
	float DefaultFOV = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Aiming Data", meta = (AllowPrivateAccess = true))
	float AimWalkSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming Data", meta = (AllowPrivateAccess = true))
	float MaxWalkSpeed = 600.0f;
	//***************************************************************

};
