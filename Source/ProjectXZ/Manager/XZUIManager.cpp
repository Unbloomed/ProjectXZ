
#include "Manager/XZUIManager.h"
#include "Widget/XZUserWidget.h"
#include"Widget/Layers/XZInGameLayer.h"
#include"Widget/Layers/XZModuleCustomizingLayer.h"
#include"Widget/Windows/XZInventoryWindow.h"

void UXZUIManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    WidgetClassMap.Add(FGameplayTag::RequestGameplayTag(FName("UI.Layer.InGameLayer")), UXZModuleCustomizingLayer::StaticClass());
    WidgetClassMap.Add(FGameplayTag::RequestGameplayTag(FName("UI.Window.InventoryWindow")), UXZInventoryWindow::StaticClass());
    WidgetClassMap.Add(FGameplayTag::RequestGameplayTag(FName("UI.Layer.ModuleCustimizingLayer")), UXZModuleCustomizingLayer::StaticClass());
}

void UXZUIManager::Deinitialize()
{
    Super::Deinitialize();
}

void UXZUIManager::PushUILayer(FGameplayTag WidgetTag)
{
    // 이미 해당 태그의 UI가 있는지 확인
    if ( UXZUserWidget* ExistingWidget = GetWidgetByTag(WidgetTag) )
    {
        HideWidget(UILayerStack.Top().Widget); // 현재 보이는 것을 숨기고
        ShowWidget(ExistingWidget);  // 해당 태그에 해당하는 UI를 표시
        UILayerStack.Push({ ExistingWidget, WidgetTag });  // 스택에 푸시
        return;
    }

    // 위젯을 생성하여 스택에 추가
    if ( UXZUserWidget* NewWidget = CreateWidgetByTag(WidgetTag) )
    {
        HideWidget(UILayerStack.Num() > 0 ? UILayerStack.Top().Widget : nullptr);  // 이전 위젯 숨김
        ShowWidget(NewWidget);  // 새로운 위젯 표시
        UILayerStack.Push({ NewWidget, WidgetTag });  // 스택에 푸시
    }
}

void UXZUIManager::PopUILayer()
{
    if ( UILayerStack.Num() > 0 )
    {
        HideWidget(UILayerStack.Top().Widget);
        UILayerStack.Pop();

        if ( UILayerStack.Num() > 0 )
        {
            ShowWidget(UILayerStack.Top().Widget);
        }
    }
}

UXZUserWidget* UXZUIManager::GetWidgetByTag(FGameplayTag WidgetTag) const
{
    for ( const FUIWidgetEntry& Entry : UILayerStack )
    {
        if ( Entry.WidgetTag == WidgetTag )
        {
            return Entry.Widget;
        }
    }
    return nullptr;
}

UXZUserWidget* UXZUIManager::CreateWidgetByTag(FGameplayTag WidgetTag)
{
    if ( TSubclassOf<UXZUserWidget>* WidgetClass = WidgetClassMap.Find(WidgetTag) )
    {
        if ( UXZUserWidget* NewWidget = CreateWidget<UXZUserWidget>(GetWorld(), *WidgetClass) )
        {
            return NewWidget;
        }
    }

    return nullptr;
}

void UXZUIManager::ShowWidget(UXZUserWidget* Widget)
{
    if ( Widget )
    {
        Widget->SetVisibility(ESlateVisibility::Visible);
    }
}

void UXZUIManager::HideWidget(UXZUserWidget* Widget)
{
    if ( Widget )
    {
        Widget->SetVisibility(ESlateVisibility::Hidden);
    }
}