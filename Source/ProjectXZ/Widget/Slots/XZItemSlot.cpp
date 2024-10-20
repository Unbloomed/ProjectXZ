#include "Widget/Slots/XZItemSlot.h"

UXZItemSlot::UXZItemSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UXZItemSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UXZItemSlotItem* SlotItem = Cast< UXZItemSlotItem>(ListItemObject);

	ItemID= SlotItem->GetItemID();
	ItemTag = SlotItem->GetItemTag();

}

void UXZItemSlotItem::OnInitialize()
{
}
