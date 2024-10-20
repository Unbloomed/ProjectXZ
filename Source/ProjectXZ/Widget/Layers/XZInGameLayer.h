// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZLayerBase.h"
#include "XZInGameLayer.generated.h"

/**
 * 
 */
class UButton;
class UXZTimerWidget;
class UXZHpBarWidget;
class UXZInventoryWindow;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryButtonClickedDelegate);

UCLASS()
class PROJECTXZ_API UXZInGameLayer : public UXZLayerBase
{
	GENERATED_BODY()
	
public:
	UXZInGameLayer(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void UpdateHPBarWidget(float CurrentHP, float MaxHP);

	FOnInventoryButtonClickedDelegate OnInventoryButtonClickedeEvent;

private:
	UFUNCTION()
	void OnInventoryButtonClicked();

private:
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<class UXZHpBarWidget> HpBarWidget;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<class UXZTimerWidget> RespawnTimerWidget;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> InventoryButton;


	FDelegateHandle HpChangedDelegateHandle;
};
