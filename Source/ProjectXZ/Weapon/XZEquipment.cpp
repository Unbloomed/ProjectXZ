#include "XZEquipment.h"

#include "GameFramework/Character.h"

void UXZEquipment::Init(ACharacter* InOwner, const FEquipmentData& InData)
{
	OwnerCharacter = InOwner;
	EquipmentData = InData;
}

void UXZEquipment::Equip()
{
	if (IsValid(EquipmentData.Montage))
	{
		OwnerCharacter->PlayAnimMontage(EquipmentData.Montage, EquipmentData.PlayRate);
	}
}
