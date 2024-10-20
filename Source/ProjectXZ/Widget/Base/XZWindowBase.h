// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/XZUserWidget.h"
#include "XZWindowBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZWindowBase : public UXZUserWidget
{
	GENERATED_BODY()
	
public:
	UXZWindowBase(const FObjectInitializer& ObjectInitializer);

	virtual void OpenWindow();
	virtual void CloseWindow();

protected:
	FGameplayTag WindowType;
};
