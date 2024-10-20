// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "XZUIManager.generated.h"

/**
 * 
 */
class UXZUserWidget;

USTRUCT()
struct FUIWidgetEntry
{
    GENERATED_BODY()

    UPROPERTY()
    TObjectPtr<UXZUserWidget> Widget;

    UPROPERTY()
    FGameplayTag WidgetTag;
};

UCLASS()
class PROJECTXZ_API UXZUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // UI Layer를 Push (열기)
    void PushUILayer(FGameplayTag WidgetTag);

    // UI Layer를 Pop (닫기)
    void PopUILayer();

    // 특정 태그로 UI Layer를 가져오기
    UXZUserWidget* GetWidgetByTag(FGameplayTag WidgetTag) const;

private:
    // UI Layer 관리 스택
    TArray<FUIWidgetEntry> UILayerStack;

    // 태그에 따른 UI Widget 생성 함수
    UXZUserWidget* CreateWidgetByTag(FGameplayTag WidgetTag);

    void ShowWidget(UXZUserWidget* Widget);
    void HideWidget(UXZUserWidget* Widget);

    // 여러 위젯을 관리하는 Map (태그별로 관리)
    TMap<FGameplayTag, TSubclassOf<UXZUserWidget>> WidgetClassMap;
};
