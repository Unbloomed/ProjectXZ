#include "WeaponContextMenu.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"

FWeaponContextMenu::FWeaponContextMenu(EAssetTypeCategories::Type InCategory)
{
	Category = InCategory;
}

FText FWeaponContextMenu::GetName() const
{
	return FText::FromString("DataAsset_Weapon");
}

UClass* FWeaponContextMenu::GetSupportedClass() const
{
	return UXZDA_Weapon::StaticClass(); // factory가 동작할 클래스 리턴.
}

FColor FWeaponContextMenu::GetTypeColor() const
{
	return FColor::Cyan;
}

uint32 FWeaponContextMenu::GetCategories()
{
	return Category; // 우클릭해서 나오는 카테고리를 리턴.
}
