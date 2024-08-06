#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponLibrary.h"
#include "XZDA_Weapon.generated.h"

class UXZWeaponData;
class AXZAttachment;
class UXZEquipment;
class UXZCombat;

/** ���� ���� ������ ����ϴ� DataAsset Ŭ����
 * 
 */

UCLASS()
class PROJECTXZ_API UXZDA_Weapon : public UDataAsset
{
	GENERATED_BODY()

public:
	UXZDA_Weapon();
	void CreateInstance(ACharacter* InOwner, UXZWeaponData** OutWeaponData);


#if WITH_EDITOR //Editor �������� ����
	void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif


private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AXZAttachment> AttachmentClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UXZEquipment> EquipmentClass;
	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UXZCombat> CombatClass;
	UPROPERTY(EditAnywhere)
	TArray<FActionData> ActionData;
	UPROPERTY(EditAnywhere)
	FBulletData BulletData;
};
