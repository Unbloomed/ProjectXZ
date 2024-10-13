#include "XZDA_Weapon.h"
#include "XZWeaponData.h"
#include "Attachment/XZAttachment.h"
#include "XZEquipment.h"
#include "Aim/XZAim.h"
#include "Combat/XZCombat.h"
#include "GameFramework/Character.h"

UXZDA_Weapon::UXZDA_Weapon()
{
	AttachmentClass = AXZAttachment::StaticClass();
	Attachment = Cast<AXZAttachment>(AttachmentClass);
	EquipmentClass = UXZEquipment::StaticClass();
	AimClass = UXZAim::StaticClass();
	CombatClass = UXZCombat::StaticClass();
}

// 객체를 생성해서 리턴한다. 생성 리턴이기 때문에 이차 포인터를 사용
void UXZDA_Weapon::CreateInstance(ACharacter* InOwner, UXZWeaponData** OutWeaponData)
{
	//XZWeaponData.h로 변수들이 이동하였기 XZAttachment, XZEquipment 객체 각각 생성.

	AXZAttachment* XZAttachment = nullptr;
	if (IsValid(AttachmentClass))//AttachmentClass가 선택되어 있다면
	{
		FActorSpawnParameters Params;
		Params.Owner = InOwner;

		XZAttachment = InOwner->GetWorld()->SpawnActor<AXZAttachment>(AttachmentClass, Params);
	}

	UXZEquipment* XZEquipment = nullptr;
	if (IsValid(EquipmentClass))
	{
		XZEquipment = NewObject<UXZEquipment>(this, EquipmentClass);
		XZEquipment->Init(XZAttachment, InOwner, EquipmentData);
	}

	UXZAim* XZAim = nullptr;
	if (IsValid(AimClass))
	{
		XZAim = NewObject<UXZAim>(this, AimClass);
		XZAim->Init(XZAttachment, InOwner, AimData);
	}

	UXZCombat* XZCombat = nullptr;
	if (IsValid(CombatClass))
	{
		XZCombat = NewObject<UXZCombat>(this, CombatClass);
		XZCombat->Init(XZAttachment, InOwner, ActionData, BulletData);
	}

	*OutWeaponData = NewObject<UXZWeaponData>();
	(*OutWeaponData)->Attachment = XZAttachment;
	(*OutWeaponData)->Equipment = XZEquipment;
	(*OutWeaponData)->Aim = XZAim;
	(*OutWeaponData)->Combat = XZCombat;
}

#if WITH_EDITOR //Editor 내에서만 수행
void UXZDA_Weapon::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	if (FApp::IsGame()) return; // 게임이 실행중이면 return
	
}
#endif