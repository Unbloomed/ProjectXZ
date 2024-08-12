#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Interface/ICombat.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "XZWeaponComponent.generated.h"

class UXZCombatHandler;
class UXZWeaponData;
class UXZDA_Weapon;
class AXZCharacter;
class AXZPlayerController;
class AXZHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZWeaponComponent : public UActorComponent, public IICombat
{
	GENERATED_BODY()

public:	
	UXZWeaponComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

//====== Get, Set Function ====================================================
public:
	TObjectPtr<AXZCharacter> GetXZCharacter();
	TObjectPtr<AXZPlayerController> GetXZPlayerController();
	const FGameplayTag& GetEquippedWeaponTag() { return EquippedWeaponTag; }

//====== Get, Set Function ====================================================

//====== Class Functions ======================================================
public:
	void AddNewWeapon(const FGameplayTag& InTag);
	UFUNCTION(Server, Reliable)
	void Server_AddNewWeapon(const FGameplayTag& InTag);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_AddNewWeapon(const FGameplayTag& InTag);

	void EquipWeapon(const FGameplayTag& InTag);
	UFUNCTION(Server, Reliable)
	void Server_EquipWeapon(const FGameplayTag& InTag);

	void UnequipWeapon(const FGameplayTag& InTag);
	UFUNCTION(Server, Reliable)
	void Server_UnequipWeapon(const FGameplayTag& InTag);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UnequipWeapon(const FGameplayTag& InTag);

	void Fire();
	UFUNCTION(Server, Reliable)
	void Server_Fire(const FVector_NetQuantize& HitLocation, const FTransform& SocketTransform);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Fire(const FVector_NetQuantize& HitLocation, const FTransform& SocketTransform);

	void Reload(const FGameplayTag& InTag);
	UFUNCTION(Server, Reliable)
	void Server_Reload(const FGameplayTag& InTag, const FTransform& SocketTransform);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Reload(const FGameplayTag& InTag, const FTransform& SocketTransform);

	void Aiming(bool bAiming);
	UFUNCTION(Server, Reliable)
	void Server_Aiming(bool bAiming);

private:
	void TraceUnderCrosshairs(FHitResult& TraceHitResult);
	void ShowCrosshair(const FGameplayTag& InTag, bool bShow);
	
//====== Class Functions ======================================================

//====== Class Variables ======================================================
private:

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Data", meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> WeaponDataTable; // Overall Weapon List

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Data", meta = (AllowPrivateAccess = true))
	TArray<FGameplayTag> Init_WeaponTags; // Initial weapons start with

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeaponTag)
	FGameplayTag EquippedWeaponTag = FXZTags::GetXZTags().Fist; // ?袁⑹삺 ?關媛?餓λ쵐???얜떯由?
	UFUNCTION()
	void OnRep_EquippedWeaponTag();

	TObjectPtr<AXZCharacter> OwnerCharacter;
	TObjectPtr<AXZPlayerController> XZPlayerController;
	FVector HitTarget; // ?μ빘釉??獄쏆뮇沅??뤾퐣 ?겸뫖猷??띿쓺 ??筌왖??


	//***************************************************************
	//** Aiming
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Aiming Data", meta = (AllowPrivateAccess = true))
	float AimWalkSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Aiming Data", meta = (AllowPrivateAccess = true))
	float MaxWalkSpeed = 600.0f;
	//***************************************************************

	

	//====== ICombat ==============================================================
public:
	void Init();
	virtual UXZCombatHandler* CreateCombatHandler() override;

private:
	UPROPERTY()
	UXZCombatHandler* CombatHandler;
	//====== ICombat ==============================================================
};