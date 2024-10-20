// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZSlotBase.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Component/XZModularComponent.h"
#include "XZModuleSlot.generated.h"

/**
 * 
 */

UCLASS()
class PROJECTXZ_API  UXZModuleSlotItem : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EModularMeshType ModuleType;
};

UCLASS()
class PROJECTXZ_API UXZModuleSlot : public UXZSlotBase, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UXZModuleSlot(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
