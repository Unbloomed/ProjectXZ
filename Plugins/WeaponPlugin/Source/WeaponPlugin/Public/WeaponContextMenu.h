#pragma once
#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 *  AssetTypeActions_Base.h 내 FAssetTypeActions_Base 클래스를 상속받아 사용
 */

class WEAPONPLUGIN_API FWeaponContextMenu : public FAssetTypeActions_Base
{
public:
	FWeaponContextMenu(EAssetTypeCategories::Type InCategory);

	//********************************************************
	//** IAssetTypeAction
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	//********************************************************

private:
	EAssetTypeCategories::Type Category;
};
