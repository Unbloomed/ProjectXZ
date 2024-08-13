#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interface/ICombat.h"
#include "UObject/NoExportTypes.h"
#include "XZCombatHandler.generated.h"

class UTimelineComponent;
class UCameraComponent;
class USpringArmComponent;
class AXZAttachment;
class AXZCharacter;
class UXZDA_Weapon;
/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZCombatHandler : public UObject
{
	GENERATED_BODY()

public:
	bool IsValidWeapon(const FGameplayTag& InTag);
	void AddNewWeapon(const FGameplayTag& InTag, UXZDA_Weapon* DA_Weapon, ACharacter* InOwner);

private:
	TMap<FGameplayTag, UXZDA_Weapon*> DA_Weapons;

	TMap<FGameplayTag, AXZAttachment*> WeaponActors;

	TObjectPtr<ACharacter> OwnerCharacter;

//====== Equip, Unequip ========================================================
public:
	void Equip(const FGameplayTag& InTag);
	void Unequip(const FGameplayTag& InTag);

private:
	void ChangeSocket_Equip(const FGameplayTag& InTag);
	void ChangeSocket_Unequip(const FGameplayTag& InTag);

	bool bEquipped = false;

	FGameplayTag EquippedTag;

//====== Equip, Unequip ========================================================
	
//====== Aim ==================================================================
public:
	TObjectPtr<USpringArmComponent> GetXZCharacterSpringArm();
	TObjectPtr<UCameraComponent> GetFollowCamera();

	void ShowCrosshair(bool bShowCrosshair);

	void StartAiming();
	void EndAiming();

private:
	void OnAiming(float Output);

	TObjectPtr<USpringArmComponent> CameraSpringArm;
	TObjectPtr<UCameraComponent> FollowCamera;
	TObjectPtr<UUserWidget> Crosshair;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> Timeline;
//====== Aim ==================================================================

//====== Fire =================================================================
public:
	void Fire(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation);

	UFUNCTION(Reliable, Server)
	void Server_Fire(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation);

	UFUNCTION(Reliable, NetMulticast)
	void Multicast_Fire(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation);
	
//====== Fire =================================================================

};
