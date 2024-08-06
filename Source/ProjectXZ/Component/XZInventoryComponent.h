#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GameplayTag/XZGameplayTags.h"
#include "XZInventoryComponent.generated.h"

class AXZItemBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZInventoryComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void Server_PickupItem();
	void PickupItem();

	UFUNCTION(Client, Reliable)
	void Client_AddtoInventory(AXZItemBase* InItem);
	void AddtoInventory(AXZItemBase* InItem);

	UFUNCTION(Server, Reliable)
	void Server_DestroyPickupItem(AXZItemBase* InItem);
	void DestroyPickupItem(AXZItemBase* InItem);

	const FGameplayTag& GetEquipSlot1() { return EquipSlot1; }
	const FGameplayTag& GetEquipSlot2() { return EquipSlot2; }
	const FGameplayTag& GetEquipSlot3() { return EquipSlot3; }
	const FGameplayTag& GetEquipSlot4() { return EquipSlot4; }

protected:
	virtual void BeginPlay() override;

private:
	FGameplayTag EquipSlot1 = FXZTags::GetXZTags().Weapon_Projectile_Pistol;
	FGameplayTag EquipSlot2 = FXZTags::GetXZTags().Weapon_Projectile_Rifle;

	UPROPERTY(Replicated)
	FGameplayTag EquipSlot3;

	UPROPERTY(Replicated)
	FGameplayTag EquipSlot4;
};
