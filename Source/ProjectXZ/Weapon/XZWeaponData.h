#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XZWeaponData.generated.h"

class UXZCombat;
class AXZAttachment;
class UXZEquipment;

/*  팩토리 패턴
 *  
 */

UCLASS()
class PROJECTXZ_API UXZWeaponData : public UObject
{
	GENERATED_BODY()

private:
	friend class UXZDA_Weapon;

public:
	FORCEINLINE AXZAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE UXZEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE UXZCombat* GetCombat() { return Combat; }

private:
	UPROPERTY()
	AXZAttachment* Attachment;

	UPROPERTY()
	UXZEquipment* Equipment;

	UPROPERTY()
	UXZCombat* Combat;
};

/*  부연설명
 *  XZDA_Weapon는 상속관계에서 분리되어 있다.
 *  XZDA_Weapon을 friend 클래스로 선언하여 XZDA_Weapon 클래스에서 XZWeaponData 클래스를 접근할 수 있게 해준다.
 *
 *	UPROPERTY를 붙여 가비지 콜렉터가 제거하기 전까지 물고 있게 만든다.
	UWeaponAsset은 UObject로부터 상속받아 Actor의 생성주기에 영향을 받지 않아 가비지 콜렉터에 영향을 받는다.
 */