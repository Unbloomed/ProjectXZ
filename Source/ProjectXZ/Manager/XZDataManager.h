// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Character/XZCharacter.h"
#include "Component/XZStatComponent.h"
#include "XZDataManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	public:
		UXZDataManager();
		virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
		FORCEINLINE FXZCharacterStat GetCharacterStat(EXZCharacterType InCharacterType) const { return CharacterStatDataMap[InCharacterType]; }
		FORCEINLINE bool  IsCharacterStatDataValid() const { return CharacterStatDataMap.IsEmpty() ? false : true; }

private:
		UPROPERTY()
		TMap<EXZCharacterType, struct FXZCharacterStat> CharacterStatDataMap;

		TObjectPtr<UDataTable> CharacterStatDataTable;
};
