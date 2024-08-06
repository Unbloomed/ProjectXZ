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
	const FGameplayTag& GetEquippedWeaponTag() { return EquippedWeaponTag; }

	UFUNCTION(Server, Reliable)
	void Server_AddNewWeapon(const FGameplayTag& InTag);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_AddNewWeapon(const FGameplayTag& InTag);
	void AddNewWeapon(const FGameplayTag& InTag);

	void EquipWeapon(const FGameplayTag& InTag);
	UFUNCTION(Server, Reliable)
	void Server_EquipWeapon(const FGameplayTag& InTag);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_EquipWeapon(const FGameplayTag& InTag);

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

protected:
	virtual void BeginPlay() override;

private:
	void TraceUnderCrosshairs(FHitResult& TraceHitResult);
	void SetHUDCrosshairs(float InDeltaTime);
	void InterpFOV(float InDeltaTime);

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Data", meta = (AllowPrivateAccess = true))
	TMap<FGameplayTag, UXZDA_Weapon*> WeaponList; // ��ü ���� ���(�����Ϳ��� ���)

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Data", meta = (AllowPrivateAccess = true))
	TArray<FGameplayTag> Init_WeaponTags; // ���� �� ������ �ִ� ����

	UPROPERTY()
	TMap<FGameplayTag, UXZWeaponData*> Datas; // ���� ������ �ִ� ����� ������

	UPROPERTY(ReplicatedUsing = OnRep_EquippedChanged)
	FGameplayTag EquippedWeaponTag = FXZTags::GetXZTags().Fist; // ���� ���� ���� ����
	UFUNCTION()
	void OnRep_EquippedChanged();

	TObjectPtr<AXZCharacter> OwnerCharacter;
	FVector HitTarget; // �Ѿ��� �߻�Ǽ� �浹�ϰ� �� ����

	//***************************************************************
	//** Crosshairs
	TObjectPtr<AXZHUD> XZHUD;
	TObjectPtr<AXZPlayerController> XZPlayerController;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> CrosshairTexture2D;
	//***************************************************************

	//***************************************************************
	//** Aiming
	UPROPERTY(ReplicatedUsing = OnRep_Aiming)
	bool bIsAiming = false;
	UFUNCTION()
	void OnRep_Aiming();

	float CurrentFOV = 90.0f; // ���� FOV ��
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Aiming Data", meta = (AllowPrivateAccess = true))
	float ZoomedFOV = 30.0f;
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Aiming Data", meta = (AllowPrivateAccess = true))
	float DefaultFOV = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Aiming Data", meta = (AllowPrivateAccess = true))
	float AimWalkSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Aiming Data", meta = (AllowPrivateAccess = true))
	float MaxWalkSpeed = 600.0f;
	//***************************************************************

};
