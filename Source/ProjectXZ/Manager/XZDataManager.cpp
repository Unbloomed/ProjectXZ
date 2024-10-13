#include "XZDataManager.h"

UXZDataManager::UXZDataManager()
{
    // CharacterStatDataTable
    static ConstructorHelpers::FObjectFinder<UDataTable> CharacterStatDataTableRef(TEXT("/Game/BP/DataTable/DT_CharacterStat.DT_CharacterStat"));
    if (CharacterStatDataTableRef.Succeeded())
    {
        CharacterStatDataTable = CharacterStatDataTableRef.Object;
    }

    // ItemTable - MainInfo
    static ConstructorHelpers::FObjectFinder<UDataTable> ItemMainInfoTableRef(TEXT("/Game/BP/DataTable/DT_ItemTable_MainInfo.DT_ItemTable_MainInfo"));
    if ( ItemMainInfoTableRef.Succeeded() )
    {
        ItemMainInfoTable = ItemMainInfoTableRef.Object;
    }

    // ItemTable - GunPartsAbilityTable
    static ConstructorHelpers::FObjectFinder<UDataTable>  GunPartsAbilityTableRef(TEXT("/Game/BP/DataTable/DT_ItemTable_GunPartsAbility.DT_ItemTable_GunPartsAbility"));
    if ( GunPartsAbilityTableRef.Succeeded() )
    {
        GunPartsAbilityTable = GunPartsAbilityTableRef.Object;
    }

    // ItemTable - ItemEquipAbilityTable
    static ConstructorHelpers::FObjectFinder<UDataTable>  EquipAbilityTableRef(TEXT("/Game/BP/DataTable/DT_ItemTable_EquipAbility.DT_ItemTable_EquipAbility"));
    if ( EquipAbilityTableRef.Succeeded() )
    {
        EquipAbilityTable = EquipAbilityTableRef.Object;
    }

    // ItemTable - GunAbilityTable
    static ConstructorHelpers::FObjectFinder<UDataTable>  GunAbilityTableRef(TEXT("/Game/BP/DataTable/DT_ItemTable_GunAbility.DT_ItemTable_GunAbility"));
    if ( GunAbilityTableRef.Succeeded() )
    {
        GunAbilityTable = GunAbilityTableRef.Object;
    }

    // ItemTable - DT_ItemTable_ModuleInfoTable
    static ConstructorHelpers::FObjectFinder<UDataTable>  ModuleInfoTableRef(TEXT("/Game/BP/DataTable/DT_ItemTable_ModuleInfo.DT_ItemTable_ModuleInfo"));
    if ( ModuleInfoTableRef.Succeeded() )
    {
        ModuleInfoTable = ModuleInfoTableRef.Object;
    }

    // ItemTable - DT_ItemTable_ModuleAssetTable
    static ConstructorHelpers::FObjectFinder<UDataTable>  ModuleAssetTableRef(TEXT("/Game/BP/DataTable/DT_ItemTable_Module.DT_ItemTable_Module"));
    if ( ModuleAssetTableRef.Succeeded() )
    {
        ModuleAssetTable = ModuleAssetTableRef.Object;
    }
    
    // Weapon List
    static ConstructorHelpers::FObjectFinder<UDataTable> WeaponDataTableDataTableRef(TEXT("/Game/BP/DataTable/DT_WeaponList.DT_WeaponList"));
    if (WeaponDataTableDataTableRef.Succeeded())
    {
        WeaponDataTable = WeaponDataTableDataTableRef.Object;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No Weapon DataTable. Check UXZDataManager::UXZDataManager"));
    }
}

void UXZDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

FXZCharacterStat* UXZDataManager::TryGetCharacterStat(FName InCharacterTypeName) const
{
    if ( !CharacterStatDataTable )
    {
        UE_LOG(LogTemp, Warning, TEXT("CharacterStatDataTable does not exist."));
        return nullptr;
    }

    FXZCharacterStat* CharacterStatRow = CharacterStatDataTable->FindRow<FXZCharacterStat>(InCharacterTypeName, TEXT("Character Stat Lookup"));

    if ( CharacterStatRow )
    {
        UE_LOG(LogTemp, Warning, TEXT("Found CharacterStatData for CharacterType: %s"), *InCharacterTypeName.ToString());
        return CharacterStatRow; 
    }

    UE_LOG(LogTemp, Warning, TEXT("Could not find CharacterStatData for CharacterType: %s"), *InCharacterTypeName.ToString());
    return nullptr; 
}

FItemTable_MainInfo* UXZDataManager::TryGetItemMainInfo(FName RowName) const
{
    if ( !ItemMainInfoTable )
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemMainInfoTable does not exist."));
        return nullptr;
    }

    FItemTable_MainInfo* ItemTable_MainInfoRow = ItemMainInfoTable->FindRow<FItemTable_MainInfo>(RowName, TEXT("Item MainInfo Lookup"));

    if ( ItemTable_MainInfoRow )
    {
        UE_LOG(LogTemp, Warning, TEXT("Found ItemMainInfoTableData for RowName: %s"), *RowName.ToString());
        return ItemTable_MainInfoRow;
    }

    UE_LOG(LogTemp, Warning, TEXT("Could not find ItemMainInfoTableData for RowName: %s"), *RowName.ToString());
    return nullptr;
}

FItemTable_GunPartsAbility* UXZDataManager::TryGetGunPartsAbility(FName RowName) const
{
    if ( !GunPartsAbilityTable )
    {
        UE_LOG(LogTemp, Warning, TEXT("Item - GunPartsAbilityTable  does not exist."));
        return nullptr;
    }

    FItemTable_GunPartsAbility* GunPartsAbilityRow = GunPartsAbilityTable->FindRow<FItemTable_GunPartsAbility>(RowName, TEXT("Item GunPartsAbilityTable Lookup"));

    if ( GunPartsAbilityRow )
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Item GunPartsAbilityTable for RowName: %s"), *RowName.ToString());
        return GunPartsAbilityRow;
    }

    UE_LOG(LogTemp, Warning, TEXT("Could not find Item GunPartsAbilityTable for RowName: %s"), *RowName.ToString());
    return nullptr;
}

FItemTable_EquipAbility* UXZDataManager::TryGetEquipAbility(FName RowName) const
{
    if ( !EquipAbilityTable )
    {
        UE_LOG(LogTemp, Warning, TEXT("Item EquipAbilityTable does not exist."));
        return nullptr;
    }

    FItemTable_EquipAbility* EquipAbilityTableRow = EquipAbilityTable->FindRow<FItemTable_EquipAbility>(RowName, TEXT("Item EquipAbilityTable Lookup"));

    if ( EquipAbilityTableRow )
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Item EquipAbilityTable for RowName: %s"), *RowName.ToString());
        return EquipAbilityTableRow;
    }

    UE_LOG(LogTemp, Warning, TEXT("Could not find Item EquipAbilityTable for RowName: %s"), *RowName.ToString());
    return nullptr;
}

FItemTable_GunAbility* UXZDataManager::TryGetGunAbility(FName RowName) const
{
    if ( !GunAbilityTable )
    {
        UE_LOG(LogTemp, Warning, TEXT("Item GunAbilityTable does not exist."));
        return nullptr;
    }

    FItemTable_GunAbility* GunAbilityTableRow = GunAbilityTable->FindRow<FItemTable_GunAbility>(RowName, TEXT("Item GunAbilityTable Lookup"));

    if ( GunAbilityTableRow )
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Item GunAbilityTable for RowName: %s"), *RowName.ToString());
        return GunAbilityTableRow;
    }

    UE_LOG(LogTemp, Warning, TEXT("Could not find Item GunAbilityTablea for RowName: %s"), *RowName.ToString());
    return nullptr;
}

FItemTable_ModuleInfo* UXZDataManager::TryGetModuleInfo(FName RowName) const
{
    if ( !ModuleInfoTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("Item ModuleInfo Table does not exist."));
        return nullptr;
    }

    FItemTable_ModuleInfo* ModuleInfoTableRow = ModuleInfoTable->FindRow<FItemTable_ModuleInfo>(RowName, TEXT("Item ModuleInfoTable Lookup"));

    if ( ModuleInfoTable )
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Item ModuleInfoTable for RowName: %s"), *RowName.ToString());
        return ModuleInfoTableRow;
    }

    UE_LOG(LogTemp, Warning, TEXT("Could not find Item ModuleInfoTable for RowName: %s"), *RowName.ToString());
    return nullptr;
}

FItemTable_Module* UXZDataManager::TryGetModuleAsset(FName RowName) const
{
    if ( !ModuleAssetTable )
    {
        UE_LOG(LogTemp, Warning, TEXT("Item ModuleAsset Table does not exist."));
        return nullptr;
    }

    FItemTable_Module* ModuleAssetTableRow = ModuleAssetTable->FindRow<FItemTable_Module>(RowName, TEXT("Item ModuleAssetTable Lookup"));

    if ( ModuleAssetTableRow )
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Item ModuleAssetTable for RowName: %s"), *RowName.ToString());
        return ModuleAssetTableRow;
    }

    UE_LOG(LogTemp, Warning, TEXT("Could not find Item ModuleAssetTable for RowName: %s"), *RowName.ToString());
    return nullptr;
}


