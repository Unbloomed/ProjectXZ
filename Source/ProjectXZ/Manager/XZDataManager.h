// Fill out your copyright notice in the Description page of Project Settings.

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
		// USkeletalMesh* TryGetSkeletalMeshModule(EModularMeshType InModuleType, int32 Index) const;

private:
		// 이렇게 되면 이중 로드되기 때문에 바로 Get해서 사용해야 한다.
		// UPROPERTY()
		// TMap<EXZCharacterType, struct FXZCharacterStat> CharacterStatDataMap;
		// UPROPERTY()
		// TMap<EModularMeshType, struct FSkeletalMeshArray> ModuleDataMap;

		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> CharacterStatDataTable;

		// UPROPERTY(EditDefaultsOnly)
		// TObjectPtr<UDataAsset> ModuleDataAsset;

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
};
