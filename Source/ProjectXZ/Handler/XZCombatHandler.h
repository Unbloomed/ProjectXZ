#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	bool IsValidWeapon(const FGameplayTag& InTag);
	
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
private:
	UPROPERTY()
	TMap<FGameplayTag, AXZAttachment*> Attachments; // 4개

	TObjectPtr<ACharacter> OwnerCharacter;

//====== Add New Weapon ========================================================
public:
	void AddNewWeapon(const FGameplayTag& InTag, ACharacter* InOwner);
	UFUNCTION(Server, Reliable)
	void Server_AddNewWeapon(const FGameplayTag& InTag);
	UFUNCTION(Client, Reliable)
	void Client_AddNewWeapon(const FGameplayTag& InTag);

private:
	TObjectPtr<UDataTable> WeaponDataTable;
//====== Add New Weapon ========================================================
	
//====== Equip, Unequip ========================================================
public:
	void Equip(const FGameplayTag& InTag);
	void Unequip(const FGameplayTag& InTag);

	void ChangeSocket_Equip(const FGameplayTag& InTag);
	void ChangeSocket_Unequip(const FGameplayTag& InTag);
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_bEquipped)
	bool bEquipped = false;
	
	UFUNCTION()
	void OnRep_bEquipped();
	
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

private:
	void OnFire(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation);
//====== Fire =================================================================

};

template <typename T>
T* UXZCombatHandler::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
