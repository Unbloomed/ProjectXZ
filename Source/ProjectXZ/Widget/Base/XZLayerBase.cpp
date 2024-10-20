#include "XZLayerBase.h"

UXZLayerBase::UXZLayerBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UXZLayerBase::OpenLayer()
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void UXZLayerBase::CloseLayer()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

// void UXZLayerBase::AddSlot(UXZSlotBase* NewSlot)
// {
// 	Slots.Push(NewSlot);
// }
