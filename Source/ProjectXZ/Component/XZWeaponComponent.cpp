#include "XZWeaponComponent.h"
#include "ProjectXZ/Character/XZCharacter.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"
#include "ProjectXZ/Weapon/XZWeaponData.h"

UXZWeaponComponent::UXZWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UXZWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	FGameplayTag Temp = FXZTags::GetXZTags().Weapon_Projectile_Rifle;

	TObjectPtr<ACharacter> character;
	TWeakObjectPtr<ACharacter> Xcharacter;

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (UXZDA_Weapon* Weapon : Init_Weapons)
	{
		// Weapon->CreateInstance(OwnerCharacter, &Datas[])
	}

}

void UXZWeaponComponent::EquipWeapon1()
{
	// TODO: 1번 슬롯의 무기의 GameplayTag를 가져옴
	FGameplayTag WeaponTag = FXZTags::GetXZTags().Weapon_Projectile_Rifle;

	if (Datas.Find(WeaponTag))
	{
		Datas[WeaponTag]->GetEquipment();
	}
}
