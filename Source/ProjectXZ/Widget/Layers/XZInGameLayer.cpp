#include "XZInGameLayer.h"
#include "Widget/XZTimerWidget.h"
#include "Widget/XZHpBarWidget.h"
#include "Character/XZCharacter.h"
#include "Component/XZStatComponent.h"
#include "Components/Button.h"
#include "Manager/XZUIManager.h"

UXZInGameLayer::UXZInGameLayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	UITag = FGameplayTag::RequestGameplayTag(FName("UI.Layer.InGameLayer"));
}

void UXZInGameLayer::NativeConstruct()
{
	Super::NativeConstruct();

	RespawnTimerWidget->SetVisibility(ESlateVisibility::Hidden);


	////////////////////////////////// Binding Delegate //////////////////////////////////
	if ( const AXZCharacter* Character = Cast< AXZCharacter>(GetOwningPlayerPawn()) )
	{
		if (UXZStatComponent* StatComponent = Character->GetStatComponent() )
		{
			HpChangedDelegateHandle =	StatComponent->OnHpChanged.AddUObject(this, &UXZInGameLayer::UpdateHPBarWidget);
		}
	}

	if ( InventoryButton )
	{
		InventoryButton->OnClicked.AddDynamic(this, &UXZInGameLayer::OnInventoryButtonClicked);
	}
	////////////////////////////////////////////////////////////////////////////

	UpdateHPBarWidget(1.0f, 1.0f);
}

void UXZInGameLayer::NativeDestruct()
{
	Super::NativeDestruct();

	if ( const AXZCharacter* Character = Cast< AXZCharacter>(GetOwningPlayerPawn()) )
	{
		if ( UXZStatComponent* StatComponent = Character->GetStatComponent() )
		{
			StatComponent->OnHpChanged.Remove(HpChangedDelegateHandle);
		}
	}
}

void UXZInGameLayer::UpdateHPBarWidget(float CurrentHP, float MaxHP)
{
	const float NewPercent = FMath::Clamp((CurrentHP / MaxHP), 0.0f, 1.0f);
	HpBarWidget->UpdateHpBar(NewPercent);
}

void UXZInGameLayer::OnInventoryButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Hidden);

	// if ( UXZUIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<UXZUIManager>() )
	// {
	// 	// 인벤토리를 열기 전 InGameLayer를 숨기고 인벤토리 창을 Push
	// 	UIManager->PushUILayer(FGameplayTag::RequestGameplayTag(FName("UI.Inventory")));
	// }

	if ( OnInventoryButtonClickedeEvent.IsBound() ) 
	{
		OnInventoryButtonClickedeEvent.Broadcast();
	}
}
