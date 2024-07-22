#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XZDA_Weapon.generated.h"

/** 무기 관련 정보를 기록하는 DataAsset 클래스
 * 
 */

UCLASS()
class PROJECTXZ_API UXZDA_Weapon : public UDataAsset
{
	GENERATED_BODY()

public:
	UXZDA_Weapon();
	void BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutWeaponData);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> AttachmentClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> EquipmentClass;
};
