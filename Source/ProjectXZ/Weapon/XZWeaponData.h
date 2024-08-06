#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XZWeaponData.generated.h"

class UXZCombat;
class AXZAttachment;
class UXZEquipment;

/*  ���丮 ����
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

/*  �ο�����
 *  XZDA_Weapon�� ��Ӱ��迡�� �и��Ǿ� �ִ�.
 *  XZDA_Weapon�� friend Ŭ������ �����Ͽ� XZDA_Weapon Ŭ�������� XZWeaponData Ŭ������ ������ �� �ְ� ���ش�.
 *
 *	UPROPERTY�� �ٿ� ������ �ݷ��Ͱ� �����ϱ� ������ ���� �ְ� �����.
	UWeaponAsset�� UObject�κ��� ��ӹ޾� Actor�� �����ֱ⿡ ������ ���� �ʾ� ������ �ݷ��Ϳ� ������ �޴´�.
 */