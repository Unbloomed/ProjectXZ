
#include "Widget/XZModuleCustomizingLayer.h"
#include "Widget/XZModuleSelectSlot.h"
#include "GameplayTag/XZGameplayTags.h"
#include "Components/ListView.h"

UXZModuleCustomizingLayer::UXZModuleCustomizingLayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	LayerType = FXZTags::GetXZTags().Widget_Layer_FullUI;
}

void UXZModuleCustomizingLayer::NativeConstruct()
{
	Super::NativeConstruct();

	const int ModuleNum = SelectSlotsInfo.Num();
	TArray< UXZModuleSelectSlotItem*>  SlotsArray;

	for ( int i = 0; i < ModuleNum; ++i )
	{
		UXZModuleSelectSlotItem* SlotItem = NewObject<UXZModuleSelectSlotItem>(this);
		SlotItem->SetSlotInfo(SelectSlotsInfo[i]);
		SlotItem->SetIndex();
		SlotsArray.Add(SlotItem);
	}

	SlotListView->SetListItems(SlotsArray);
}

