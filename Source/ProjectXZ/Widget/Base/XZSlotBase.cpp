#include "XZSlotBase.h"

UXZSlotBase::UXZSlotBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UXZSlotBase::SetParentLayer(XZLayerBase* NewParentLayer)
{
	ParentLayer = NewParentLayer;
}
