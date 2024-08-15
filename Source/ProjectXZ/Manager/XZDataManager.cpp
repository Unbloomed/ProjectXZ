#include "XZDataManager.h"

UXZDataManager::UXZDataManager()
{
    // BossAttackDataArray
    static ConstructorHelpers::FObjectFinder<UDataTable> CharacterStatDataTableRef(TEXT("/Game/BP/DataTable/DT_CharacterStat.DT_CharacterStat"));
    if (CharacterStatDataTableRef.Succeeded())
    {
        CharacterStatDataTable = CharacterStatDataTableRef.Object;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No Character Stat DataTable. Check UXZDataManager::UXZDataManager"));
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

	if (CharacterStatDataTable)
	{
        FString ContextString;
        const TMap<FName, uint8*>& RowMap = CharacterStatDataTable->GetRowMap();
        int index = 0;
        for (auto& Entry : RowMap)
        {
            FXZCharacterStat* CharacterStat = (FXZCharacterStat*)Entry.Value;
            if (CharacterStat)
            {
                CharacterStatDataMap.Add(CharacterStat->CharacterType, *CharacterStat);
            }
        }
	}
}
