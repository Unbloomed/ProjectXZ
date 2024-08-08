// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XZUserWidget.h"
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

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpProgressBar;

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHpBar(float NewCurrentHp);

protected:

	UPROPERTY()
	float MaxHp;
};
