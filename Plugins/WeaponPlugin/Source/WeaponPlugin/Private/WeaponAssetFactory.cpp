#include "WeaponAssetFactory.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"

UWeaponAssetFactory::UWeaponAssetFactory()
{
	bCreateNew = true;

	// Factory.h�� SupportedClass�� ����.  �� factory���� ������ Ŭ���� Ÿ���� UXZDA_Weapon�� ����.
	SupportedClass = UXZDA_Weapon::StaticClass();
}

// ������ ���� ����.
UObject* UWeaponAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	return NewObject<UXZDA_Weapon>(InParent, InClass, InName, Flags);
}
