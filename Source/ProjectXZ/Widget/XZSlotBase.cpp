// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/XZSlotBase.h"

UXZSlotBase::UXZSlotBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UXZSlotBase::SetParentLayer(XZLayerBase* NewParentLayer)
{
	ParentLayer = NewParentLayer;
}
