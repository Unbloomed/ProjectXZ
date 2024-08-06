#include "XZEquipment.h"
#include "Attachment/XZAttachment.h"
#include "GameFramework/Character.h"

void UXZEquipment::Init(AXZAttachment* InWeapon, ACharacter* InOwner, const FEquipmentData& InData)
{
	WeaponAttachment = InWeapon;
	OwnerCharacter = InOwner;
	EquipmentData = InData;

	// ���ӽ��� �� ���� ����
	if (InData.HolsterSocketName.IsValid())
	{
		InWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InData.HolsterSocketName);
	}
}

bool UXZEquipment::Equip()
{
	// TODO: �ӽ�. Unequip ���� ��ȭ�ϱ�
	if (bEquipped)
	{
		Unequip();
		return false;
	}

	if (IsValid(EquipmentData.EquipMontage))
	{
		OwnerCharacter->PlayAnimMontage(EquipmentData.EquipMontage);

		FTimerHandle EquipTimerHandle;
		FTimerDelegate EquipTimerDelegate = FTimerDelegate::CreateUObject(this, &ThisClass::EquipChangeSocket);
		OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(EquipTimerHandle, EquipTimerDelegate, EquipmentData.Equip_FrameTime, false);

		bEquipped = true;

		return true;
	}

	return false;
}

void UXZEquipment::Unequip()
{
	if (IsValid(EquipmentData.UnequipMontage))
	{
		OwnerCharacter->PlayAnimMontage(EquipmentData.UnequipMontage);

		FTimerHandle UnequipTimerHandle;
		FTimerDelegate UnequipTimerDelegate = FTimerDelegate::CreateUObject(this, &ThisClass::UnequipChangeSocket);
		OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(UnequipTimerHandle, UnequipTimerDelegate, EquipmentData.Unequip_FrameTime, false);

		bEquipped = false;
	}
}

void UXZEquipment::EquipChangeSocket()
{
	if (EquipmentData.WeaponSocketName.IsValid())
	{
		WeaponAttachment->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), EquipmentData.WeaponSocketName);
	}
}

void UXZEquipment::UnequipChangeSocket()
{
	if (EquipmentData.HolsterSocketName.IsValid())
	{
		WeaponAttachment->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), EquipmentData.HolsterSocketName);
	}
}

