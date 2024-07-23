#pragma once
#include "CoreMinimal.h"
#include "WeaponLibrary.h"
#include "UObject/NoExportTypes.h"
#include "XZEquipment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZEquipment : public UObject
{
	GENERATED_BODY()

public:
	void Init(class ACharacter* InOwner, const FEquipmentData& InData);

	void Equip();


private:
	ACharacter* OwnerCharacter;
	FEquipmentData EquipmentData;

};
