#include "XZHUD.h"
#include "Character/XZCharacter.h"
#include "Widget/XZHpBarWidget.h"
#include "Widget/XZTimerWidget.h"

AXZHUD::AXZHUD() 
{

}

void AXZHUD::DrawHUD()
{
	Super::DrawHUD();

	APlayerController* PC = GetOwningPlayerController();
	if (IsValid(PC) && CharacterOverlayWidgetClass)
	{
		CharacterOverlayWidget = CreateWidget<UUserWidget>(PC, CharacterOverlayWidgetClass);
	}
}

void AXZHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(CharacterOverlayWidget))
	{
		CharacterOverlayWidget->AddToViewport();
		CharacterOverlayWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (PlayerOwner == nullptr)
	{
		return;
	}

	//////////////////////////////////// HP ////////////////////////////////////
	// Create HpBarWidget
	if (IsValid(HpBarWidgetClass))
	{
		HpBarWidget = CreateWidget<UXZHpBarWidget>(PlayerOwner, HpBarWidgetClass, TEXT("HpBarWidget"));
		if (IsValid(HpBarWidget))
		{
			HpBarWidget->AddToViewport();
		}
	}
	////////////////////////////////////////////////////////////////////////////

	//////////////////////////////// RespawnTimer ////////////////////////// 
	// Create HpBarWidget
	if (IsValid(RespawnTimerWidgetClass))
	{
		RespawnTimerWidget = CreateWidget<UXZTimerWidget>(PlayerOwner, RespawnTimerWidgetClass, TEXT("ReapwnTimerWidget"));
		if (IsValid(RespawnTimerWidget))
		{
			RespawnTimerWidget->AddToViewport();
			RespawnTimerWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////// Binding Delegate 
	if (AXZCharacter* Character = Cast<AXZCharacter>(PlayerOwner->GetPawn()))
	{
		Character->SetUpWidget(this);
	}
	////////////////////////////////////////////////////////////////////////////
}

void AXZHUD::UpdateHPBarWidget(float CurrentHP, float MaxHP)
{
	const float NewPercent = FMath::Clamp((CurrentHP / MaxHP), 0.0f, 1.0f);
	HpBarWidget->UpdateHpBar(NewPercent);
}
