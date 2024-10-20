
#include "XZModuleCustomizingLayer.h"
#include "Widget/Slots/XZModuleSelectSlot.h"
#include "GameplayTag/XZGameplayTags.h"
#include "Components/ListView.h"

UXZModuleCustomizingLayer::UXZModuleCustomizingLayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	LayerType = FXZTags::GetXZTags().Widget_UIType_FullUI;

	UITag = FGameplayTag::RequestGameplayTag(FName("UI.Layer.ModuleCustimizingLayer"));
}

void UXZModuleCustomizingLayer::NativeConstruct()
{
	Super::NativeConstruct();

	const int ModuleNum = SelectSlotsInfo.Num();
	TArray< UXZModuleSelectSlotItem*>  SlotsArray;

	for ( int i = 0; i < ModuleNum; ++i )
	{
		UXZModuleSelectSlotItem* SlotItem = NewObject<UXZModuleSelectSlotItem>(this);
		SlotItem->InitializeData(SelectSlotsInfo[i].ModuleType);
		SlotsArray.Add(SlotItem);
	}

	SlotListView->SetListItems(SlotsArray);
}

