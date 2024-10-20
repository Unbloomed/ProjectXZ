// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZSlotBase.h"
#include "Component/XZModularComponent.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "XZModuleSelectSlot.generated.h"

/**
 * 
 */
class UButton;
class UImage;
class UTextBlock;

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
    UXZModuleSelectSlotItem() {  }

    void InitializeData(EModularMeshType NewModuleType);
    
    FORCEINLINE const FModuleIndexInfo GetIndexInfo() const { return IndexInfo; }
    FORCEINLINE const EModularMeshType GetModuleType() const { return ModuleType; }

private:
    void OnInitialize();
    // void OnUpdate();
    // void OnDestroy();

    void CalculateItemIndexRange();

    FModuleIndexInfo IndexInfo;
    EModularMeshType ModuleType;
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModuleChangedDelegate, EModularMeshType ModuleType, const int32 itemID);

UCLASS()
class PROJECTXZ_API UXZModuleSelectSlot : public UXZSlotBase, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
    UXZModuleSelectSlot(const FObjectInitializer& ObjectInitializer);
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

public:
    UFUNCTION()
    void OnPrevButtonClicked();

    UFUNCTION()
    void OnNextButtonClicked();
protected:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
    void OnUpdate();
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

    FDelegateHandle ModularComponentDelegateHandle;
};
