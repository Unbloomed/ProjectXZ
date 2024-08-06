#pragma once
#include "CoreMinimal.h"
#include "WeaponLibrary.h"
#include "XZEquipment.generated.h"

/** Equipment Ŭ����
 * 
 */
UCLASS()
class PROJECTXZ_API UXZEquipment : public UObject
{
	GENERATED_BODY()

public:
	void Init(class AXZAttachment* InWeapon, ACharacter* InOwner, const FEquipmentData& InData);

	bool Equip();
	void Unequip();
	void EquipChangeSocket();
	void UnequipChangeSocket();

private:
	TObjectPtr<AXZAttachment> WeaponAttachment;

	ACharacter* OwnerCharacter;
	FEquipmentData EquipmentData;

	bool bEquipped = false;
};
