#include "Component/XZInventoryComponent.h"
#include "GameplayTag/XZGameplayTags.h"

UXZInventoryComponent::UXZInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	EquipSlot1 = FXZTags::GetXZTags().Weapon_Projectile_Pistol;
	EquipSlot2 = FXZTags::GetXZTags().Weapon_Projectile_Rifle;
	EquipSlot3 = FXZTags::GetXZTags().Weapon_Projectile_SMG;
	EquipSlot4 = FXZTags::GetXZTags().Weapon_Hitscan_Shotgun;
}


void UXZInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

