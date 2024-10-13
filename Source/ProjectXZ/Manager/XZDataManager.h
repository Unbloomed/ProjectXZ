#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Character/XZCharacter.h"
#include "Component/XZStatComponent.h"
#include "Component/XZModularComponent.h"
#include "Modular/XZItemTable.h"
#include "XZDataManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTXZ_API UXZDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
		UXZDataManager();
		virtual void Initialize(FSubsystemCollectionBase& Collection) override;

		FXZCharacterStat* TryGetCharacterStat(FName RowName) const;
		FItemTable_MainInfo* TryGetItemMainInfo(FName RowName) const;
		FItemTable_GunPartsAbility* TryGetGunPartsAbility(FName RowName) const;
		FItemTable_EquipAbility* TryGetEquipAbility(FName RowName) const;
		FItemTable_GunAbility* TryGetGunAbility(FName RowName) const;
		FItemTable_ModuleInfo* TryGetModuleInfo(FName RowName) const;
		FItemTable_Module* TryGetModuleAsset(FName RowName) const;
		
		FORCEINLINE UDataTable* GetWeaponDataTable() { return  WeaponDataTable; }
	
private:
		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> CharacterStatDataTable;

		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> ItemMainInfoTable;
		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> GunPartsAbilityTable;
		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> EquipAbilityTable;
		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> GunAbilityTable;
		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> ModuleInfoTable;
		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> ModuleAssetTable;
	
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Data", meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> WeaponDataTable; // Overall Weapon List
};
