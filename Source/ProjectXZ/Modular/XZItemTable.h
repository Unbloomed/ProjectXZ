// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Component/XZModularComponent.h"
#include "XZItemTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTXZ_API FItemTable_MainInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemTable_MainInfo() { }
	FItemTable_MainInfo(FString _ItemName,int32 _ID, int32 _CategoryID, int32 _CategoryKey, int32 _Ability1, int32 _Ability2,
		FGameplayTag _Tag, FString _Name, FString _Description_Kor, FString _ImagePath, FString _DataAsset) :
		ITEMNAME(_ItemName), ID(_ID), CATEGORY_ID(_CategoryID), CATEGORY_KEY(_CategoryKey), ABILITY_1(_Ability1), ABILITY_2(_Ability2), TAG(_Tag),
		DESCRIPTION(_Description_Kor), IMAGEPATH(_ImagePath), DATAASSET(_DataAsset)
	{  }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString ITEMNAME;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 CATEGORY_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 CATEGORY_KEY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ABILITY_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ABILITY_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FGameplayTag TAG;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString DESCRIPTION;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString IMAGEPATH;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString DATAASSET;
};

USTRUCT(BlueprintType)
struct PROJECTXZ_API FItemTable_GunAbility : public FTableRowBase
{
	GENERATED_BODY()
	public:
	FItemTable_GunAbility() { }
	FItemTable_GunAbility(int32 _ID, int32 _Capacity, int32 _Attack, int32 _AttackCoeff, int32 _BurstDelay, int32 _ReloadDelay, int32 _MinDistance, int32 _MaxDistance)
		:ID(_ID), Capacity(_Capacity), Attack(_Attack), AttackCoeff(_AttackCoeff), BurstDelay(_BurstDelay), ReloadDelay(_ReloadDelay), MinDistance(_MinDistance), MaxDistance(_MaxDistance) {  }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunAbility)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunAbility)
	int32 Capacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunAbility)
	int32	Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunAbility)
	int32 AttackCoeff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunAbility)
	int32	BurstDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunAbility)
	int32 ReloadDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunAbility)
	int32 MinDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunAbility)
	int32 MaxDistance;
	};


USTRUCT(BlueprintType)
struct PROJECTXZ_API FItemTable_EquipAbility : public FTableRowBase
{
	GENERATED_BODY()
	public:
	FItemTable_EquipAbility() { }
	FItemTable_EquipAbility(int32 _ID, int32 _Defense, int32 _Weight)
		:ID(_ID), Defense(_Defense), Weight(_Weight) {  }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipAbility)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipAbility)
	int32 Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipAbility)
	int32	Weight;
};

USTRUCT(BlueprintType)
struct PROJECTXZ_API FItemTable_GunPartsAbility : public FTableRowBase
{
	GENERATED_BODY()
	public:
		FItemTable_GunPartsAbility() { }
		FItemTable_GunPartsAbility(int32 _ID, int32 _HideMuzzle, int32 _DeltaDynamic, int32 _SoundVolume, int32 _YawRecoil, int32 _PitchRecoil, 
			int32 _AimingTime, int32 _Fov, int32 _Magnification, int32 _Variable_Magnification, int32 _ReloadRate, int32 _AimingRate)
			: ID(_ID), HideMuzzle(_HideMuzzle), DeltaDynamic(_DeltaDynamic), SoundVolume(_SoundVolume), YawRecoil(_YawRecoil), PitchRecoil(_PitchRecoil), 
			AimingTime(_AimingTime), Fov(_Fov), Magnification(_Magnification), Variable_Magnification(_Variable_Magnification), ReloadRate(_ReloadRate), AimingRate(_AimingRate) {  }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunPartsAbility)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunPartsAbility)
	int32 HideMuzzle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	DeltaDynamic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	SoundVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	YawRecoil;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	PitchRecoil;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	AimingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	Fov;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	Magnification;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	Variable_Magnification;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	ReloadRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipGunPartsAbilityAbility)
	int32	AimingRate;
};

// RowName	ID	GameplayTag
USTRUCT(BlueprintType)
struct PROJECTXZ_API FItemTable_ModuleInfo : public FTableRowBase
{
	GENERATED_BODY()
	public:
		FItemTable_ModuleInfo() { }
		FItemTable_ModuleInfo(int32 _ID, EModularMeshType _ModuleType, FGameplayTag _Tag)
		: ID(_ID), ModuleType(_ModuleType), Tag(_Tag), Obtainable(false), ColumnIndex(0),RowIndex(0), MaterialPath(TEXT(""))
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModuleInfo)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModuleInfo)
	EModularMeshType ModuleType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModuleInfo)
	FGameplayTag Tag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	uint8 Obtainable : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	int32  ColumnIndex ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	int32  RowIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	FString MaterialPath;

};

USTRUCT(BlueprintType)
struct PROJECTXZ_API FItemTable_Module : public FTableRowBase
{
	GENERATED_BODY()
	public:
		FItemTable_Module() { }
		FItemTable_Module(int32 _ID, int32 _CATEGORY_ID, FString _ASSETNAME, FString _ASSETPATH, FString _IMAGEPATH)
			: ID(_ID), CATEGORY_ID(_CATEGORY_ID), ASSETNAME(_ASSETNAME), ASSETPATH(_ASSETPATH), IMAGEPATH(_IMAGEPATH)
		{
		}
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	int32 CATEGORY_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	FString	ASSETNAME;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	FString	ASSETPATH;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Module)
	FString	IMAGEPATH;

};