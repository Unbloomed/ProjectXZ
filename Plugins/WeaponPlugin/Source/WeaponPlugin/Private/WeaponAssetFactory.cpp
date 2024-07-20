#include "WeaponAssetFactory.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"

UWeaponAssetFactory::UWeaponAssetFactory()
{
	bCreateNew = true;

	// Factory.h의 SupportedClass을 설정. 무기 데이터에셋의 클래스 타입으로 factory 설정.
	SupportedClass = UXZDA_Weapon::StaticClass();
}

// 에셋을 새로 생성.
UObject* UWeaponAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	return NewObject<UXZDA_Weapon>(InParent, InClass, InName, Flags);
}
