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
	UFUNCTION(Server, Reliable)
	void Server_Aiming(bool bAiming);

protected:
	virtual void BeginPlay() override;

private:
	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Data", meta = (AllowPrivateAccess = true))
	TMap<FGameplayTag, UXZDA_Weapon*> WeaponList; // 전체 무기 목록(에디터에서 등록)

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Data", meta = (AllowPrivateAccess = true))
	TArray<FGameplayTag> Init_WeaponTags; // 시작 시 가지고 있는 무기

	UPROPERTY()
	TMap<FGameplayTag, UXZWeaponData*> Datas; // 현재 가지고 있는 무기들 데이터

	UPROPERTY(ReplicatedUsing = OnRep_EquippedChanged)
	FGameplayTag EquippedWeaponTag = FXZTags::GetXZTags().Fist; // 현재 장착 중인 무기
	UFUNCTION()
	void OnRep_EquippedChanged();

	TObjectPtr<AXZCharacter> OwnerCharacter;
	TObjectPtr<AXZPlayerController> XZPlayerController;
	FVector HitTarget; // 총알이 발사되서 충돌하게 될 지점


	//***************************************************************
	//** Aiming
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Aiming Data", meta = (AllowPrivateAccess = true))
	float AimWalkSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Aiming Data", meta = (AllowPrivateAccess = true))
	float MaxWalkSpeed = 600.0f;
	//***************************************************************

};
