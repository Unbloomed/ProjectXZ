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

	FVector2D ViewportSize;
	if (IsValid(GEngine))
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2D ViewportCenter(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f);

		if (CrosshairTexture2D) 
		{
			DrawCrosshair(CrosshairTexture2D, ViewportCenter, FLinearColor::White);
		}

		APlayerController* PC = GetOwningPlayerController();
		if (IsValid(PC) && CharacterOverlayWidgetClass)
		{
			CharacterOverlayWidget = CreateWidget<UUserWidget>(PC, CharacterOverlayWidgetClass);
		}
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


void AXZHUD::DrawCrosshair(UTexture2D* InTexture, FVector2D ViewportCenter, FLinearColor CrosshairColor)
{
	const float TextureWidth = InTexture->GetSizeX();  // Texture ?ˆë¹„
	const float TextureHeight = InTexture->GetSizeY(); // Texture ?’ì´

	// Texture ê·¸ë¦¬ê¸??„ì¹˜ ?¤ì •
	const FVector2D TextureDrawPoint(
		ViewportCenter.X - (TextureWidth / 2.0f),
		ViewportCenter.Y - (TextureHeight / 2.0f)
	);

	// Texture ê·¸ë¦¬ê¸?
	DrawTexture(InTexture, TextureDrawPoint.X, TextureDrawPoint.Y, TextureWidth, TextureHeight, 0.0f, 0.0f, 1.0f, 1.0f, CrosshairColor);
}


void AXZHUD::UpdateHPBarWidget(float CurrentHP, float MaxHP)
{
	const float NewPercent = FMath::Clamp((CurrentHP / MaxHP), 0.0f, 1.0f);
	HpBarWidget->UpdateHpBar(NewPercent);
}

// void AXZHUD::StartRespawnTimer(float RespawnDelayTime)
// {
// 	if (RespawnTimerWidget) 
// 	{
// 		RespawnTimerWidget->StartTimer(RespawnDelayTime);
// 	}
// }

