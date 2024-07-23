#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponLibrary.h"
#include "XZDA_Weapon.generated.h"

class UXZWeaponData;
class AXZAttachment;
class UXZEquipment;

/** 무기 관련 정보를 기록하는 DataAsset 클래스
 * 
 */

UCLASS()
class PROJECTXZ_API UXZDA_Weapon : public UDataAsset
{
	GENERATED_BODY()

public:
	UXZDA_Weapon();
	void CreateInstance(ACharacter* InOwner, UXZWeaponData** OutWeaponData);


#if WITH_EDITOR //Editor 내에서만 수행
	void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif


private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AXZAttachment> AttachmentClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UXZEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;

};
