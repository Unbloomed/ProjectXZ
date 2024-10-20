// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/XZUserWidget.h"
#include "GameplayTag/XZGameplayTags.h"
#include "XZLayerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZLayerBase : public UXZUserWidget
{
	GENERATED_BODY()
	
public:
	UXZLayerBase(const FObjectInitializer& ObjectInitializer);

	void OpenLayer();
	void CloseLayer();

protected:
	FGameplayTag LayerType;
};
