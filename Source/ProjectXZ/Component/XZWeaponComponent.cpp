#include "XZWeaponComponent.h"
#include "ProjectXZ/Character/XZCharacter.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"
#include "ProjectXZ/Weapon/XZEquipment.h"
#include "ProjectXZ/Weapon/XZWeaponData.h"

UXZWeaponComponent::UXZWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UXZWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// 무기 목록
	for (const TTuple<FGameplayTag, UXZDA_Weapon*>& Weapon : WeaponList)
	{
		UXZWeaponData* Temp = NewObject<UXZWeaponData>(this);
		Datas.Add(Weapon.Key, Temp);
	}

	// 시작 무기 생성
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (const FGameplayTag& Tag : Init_WeaponTags)
	{
		WeaponList[Tag]->CreateInstance(OwnerCharacter, &Datas[Tag]);
	}
}

void UXZWeaponComponent::EquipWeapon(const FGameplayTag& InTag)
{
	// 슬롯에 등록된 무기의 GameplayTag를 InTag로 가져옴

	if (UXZWeaponData** FoundData = Datas.Find(InTag))
	{
		if (*FoundData)
		{
			(*FoundData)->GetEquipment()->Equip();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FoundData(=XZWeaponData) is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameplayTag is not found in Datas"));
	}
}

void UXZWeaponComponent::Fire(const FGameplayTag& InTag)
{
	if (UXZWeaponData** FoundData = Datas.Find(InTag))
	{
		if (*FoundData)
		{
			// 
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FoundData(=XZWeaponData) is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameplayTag is not found in Datas"));
	}
}
