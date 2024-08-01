#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GameplayTag/XZGameplayTags.h"
#include "XZInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZInventoryComponent();
	FGameplayTag& GetEquipSlot1() { return EquipSlot1; }
	FGameplayTag& GetEquipSlot2() { return EquipSlot2; }
	FGameplayTag& GetEquipSlot3() { return EquipSlot3; }
	FGameplayTag& GetEquipSlot4() { return EquipSlot4; }

protected:
	virtual void BeginPlay() override;

private:
	//UPROPERTY()
	FGameplayTag EquipSlot1 = FXZTags::GetXZTags().Weapon_Projectile_Pistol;
	//UPROPERTY()
	FGameplayTag EquipSlot2 = FXZTags::GetXZTags().Weapon_Projectile_Rifle;
	//UPROPERTY()
	FGameplayTag EquipSlot3 = FXZTags::GetXZTags().Weapon_Projectile_SMG;
	//UPROPERTY()
	FGameplayTag EquipSlot4 = FXZTags::GetXZTags().Weapon_Hitscan_Shotgun;
		
};
