// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/XZHUDBase.h"
#include "XZCustomizationHUD.generated.h"

class UXZModuleCustomizingLayer;
/**
 * 
 */
UCLASS()
class PROJECTXZ_API AXZCustomizationHUD : public AXZHUDBase
{
	GENERATED_BODY()
public:
	AXZCustomizationHUD();
virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "XZ|CustomizingLyaer", Meta = ( AllowPrivateAccess = "true" ))
	TSubclassOf< UXZModuleCustomizingLayer> CustomizingLayerClass;

	TObjectPtr< UXZModuleCustomizingLayer> CustomizingLayer;
};
