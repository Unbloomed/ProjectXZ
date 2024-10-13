// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "XZHUDBase.generated.h"

/**
 * 
 */
class UXZModuleCustomizingLayer;

UCLASS()
class PROJECTXZ_API AXZHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	AXZHUDBase();
	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;
};
