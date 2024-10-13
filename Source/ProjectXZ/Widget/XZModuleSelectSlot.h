// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/XZSlotBase.h"
#include "Component/XZModularComponent.h"
#include "Widget/XZModuleCustomizingLayer.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "XZModuleSelectSlot.generated.h"

/**
 * 
 */
class UButton;
class UImage;
class UTextBlock;
struct FXZModuleSelectSlotInfo;

// Data
UCLASS()
class PROJECTXZ_API UXZModuleSelectSlotItem : public UObject
{
    GENERATED_BODY()
    
public:
    struct FModuleIndexInfo
    {
    public:
        FModuleIndexInfo() :ItemBaseID(-1), ItemLastID(-1) {  }
        FModuleIndexInfo(int32 NewItemBaseID, int32 NewItemLastID) :ItemBaseID(NewItemBaseID), ItemLastID(NewItemLastID) {  }
        int32 ItemBaseID;
        int32 ItemLastID;
    };

public:
    UXZModuleSelectSlotItem() {}
    FORCEINLINE const FXZModuleSelectSlotInfo GetSlotInfo() const { return SlotInfo; }
    FORCEINLINE const FModuleIndexInfo GetIndexInfo() const { return IndexInfo; }
    FORCEINLINE void SetSlotInfo(const FXZModuleSelectSlotInfo NewSlotinfo)  { SlotInfo = NewSlotinfo;}

    void SetIndex();

private:
    UPROPERTY(EditDefaultsOnly, Category = "XZ|Widget", meta = ( AllowPrivateAccess = true ))
    FXZModuleSelectSlotInfo SlotInfo;
    FModuleIndexInfo IndexInfo;
};

// DECLARE_MULTICAST_DELEGATE_OneParam(FOnModuleTypeChangedDelegate, const EModularMeshType NewModuleType);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectModuleChangedDelegate, const int32 itemID);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModuleChangedDelegate, EModularMeshType ModuleType, const int32 itemID);

UCLASS()
class PROJECTXZ_API UXZModuleSelectSlot : public UXZSlotBase, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
    UXZModuleSelectSlot(const FObjectInitializer& ObjectInitializer);
   virtual void NativeConstruct() override;

public:
    UFUNCTION()
    void OnPrevButtonClicked();

    UFUNCTION()
    void OnNextButtonClicked();

    UFUNCTION()
    void SetModuleType(const EModularMeshType NewModuleType);



protected:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
    void SetModuleImage();
    void SetCurrentSelectItemID(const int32 itemID);
    void SetModuleText();

public:
    FOnModuleChangedDelegate OnModuleChanged;
private:
    // 구성 요소
    UPROPERTY(meta = ( BindWidget ))
    TObjectPtr<UButton> PrevButton;

    UPROPERTY(meta = ( BindWidget ))
    TObjectPtr<UButton> NextButton;

    UPROPERTY(meta = ( BindWidget ))
    TObjectPtr<UImage> PreviewImage;

    UPROPERTY(meta = ( BindWidget ))
    TObjectPtr<UTextBlock> ModuleName;

    UPROPERTY()
    TObjectPtr<UMaterialInstance> SlotMaterialInstance;

    UPROPERTY()
    TObjectPtr<UMaterialInstanceDynamic> SlotMaterialInstanceDynamic;

    UPROPERTY()
    EModularMeshType ModuleType;

    UXZModuleSelectSlotItem::FModuleIndexInfo IndexInfo;
    int32 CurrentIndex = 0;
};
