#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Character/XZCharacter.h"
#include "Component/XZStatComponent.h"
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
		
		FORCEINLINE FXZCharacterStat GetCharacterStat(EXZCharacterType InCharacterType) const { return CharacterStatDataMap[InCharacterType]; }
		FORCEINLINE bool  IsCharacterStatDataValid() const { return CharacterStatDataMap.IsEmpty() ? false : true; }
		FORCEINLINE UDataTable* GetWeaponDataTable() { return  WeaponDataTable; }
	
private:
		UPROPERTY()
		TMap<EXZCharacterType, struct FXZCharacterStat> CharacterStatDataMap;

		UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UDataTable> CharacterStatDataTable;
	
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Weapon Data", meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> WeaponDataTable; // Overall Weapon List
};
