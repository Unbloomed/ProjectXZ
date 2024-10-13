// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/XZUserWidget.h"
#include "XZSlotBase.generated.h"

/**
 * 
 */
class XZLayerBase;
UCLASS()
class PROJECTXZ_API UXZSlotBase : public UXZUserWidget
{
	GENERATED_BODY()
public:
	UXZSlotBase(const FObjectInitializer& ObjectInitializer);
	void SetParentLayer(XZLayerBase* NewParentLayer);
protected:
	TObjectPtr< XZLayerBase> ParentLayer;
	
};
