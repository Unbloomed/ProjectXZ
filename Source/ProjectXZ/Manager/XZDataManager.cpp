// Fill out your copyright notice in the Description page of Project Settings.


#include "XZDataManager.h"

UXZDataManager::UXZDataManager()
{
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
