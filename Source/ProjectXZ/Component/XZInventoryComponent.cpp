#include "Component/XZInventoryComponent.h"
#include "Character/XZCharacter.h"
#include "GameplayTag/XZGameplayTags.h"
#include "Item/XZItemBase.h"
#include "Net/UnrealNetwork.h"

UXZInventoryComponent::UXZInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UXZInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}

void UXZInventoryComponent::PickupItem()
{
	Server_PickupItem();
}

void UXZInventoryComponent::Server_PickupItem_Implementation()
{
	TArray<AActor*> OverlappingActors;
	AXZCharacter* XZCharacter = Cast<AXZCharacter>(GetOwner());
	XZCharacter->GetOverlappingActors(OverlappingActors, AXZItemBase::StaticClass());

	if (OverlappingActors.Num() > 0)
	{
		for (AActor* const& Item : OverlappingActors)
		{
			UE_LOG(LogTemp, Log, TEXT("Overlapping Actor!  UXZInventoryComponent::Server_PickupItem_Implementation"));

			AXZItemBase* OverlappingItem = Cast<AXZItemBase>(Item);
			AddtoInventory(OverlappingItem);
		}
	}
}

void UXZInventoryComponent::AddtoInventory(AXZItemBase* InItem)
{
	Client_AddtoInventory(InItem);
}

void UXZInventoryComponent::Client_AddtoInventory_Implementation(AXZItemBase* InItem)
{
	UE_LOG(LogTemp, Log, TEXT("Pickup and then Add to Inventory!  Client_AddtoInventory_Implementation"));

	DestroyPickupItem(InItem);
}

void UXZInventoryComponent::DestroyPickupItem(AXZItemBase* InItem)
{
	Server_DestroyPickupItem(InItem);
}

void UXZInventoryComponent::Server_DestroyPickupItem_Implementation(AXZItemBase* InItem)
{
	InItem->Destroy(); // 아이템 제거
}

void UXZInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

