// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/XZUserWidget.h"
#include "XZHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZHpBarWidget : public UXZUserWidget
{
	GENERATED_BODY()

public:
		UXZHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
