#include "XZHUD.h"
#include "Widget/XZHpBarWidget.h"

AXZHUD::AXZHUD() 
{
	static ConstructorHelpers::FClassFinder<UXZHpBarWidget> HpBarWidgetClassRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP/Widget/BP_TestHPBar.BP_TestHPBar_C'"));
	if (HpBarWidgetClassRef.Class)
	{
		HpBarWidgetClass = HpBarWidgetClassRef.Class;
	}
}

void AXZHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ViewportSize;
	if (IsValid(GEngine))
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2D ViewportCenter(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f);

		// Crosshair 洹몃━湲?
		DrawCrosshair(CrosshairTexture2D, ViewportCenter, FLinearColor::White);

		// 罹먮┃???곹깭李?
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

	// Create HpBarWidget
	if (HpBarWidgetClass)
	{
		HpBarWidget = CreateWidget<UXZHpBarWidget>(PlayerOwner, HpBarWidgetClass, TEXT("HpBarWidget"));
		if (HpBarWidget)
		{
			HpBarWidget->AddToViewport();
		}
	}
}


void AXZHUD::DrawCrosshair(UTexture2D* InTexture, FVector2D ViewportCenter, FLinearColor CrosshairColor)
{
	const float TextureWidth = InTexture->GetSizeX();  // Texture ?덈퉬
	const float TextureHeight = InTexture->GetSizeY(); // Texture ?믪씠

	// Texture 洹몃━湲??꾩튂 ?ㅼ젙
	const FVector2D TextureDrawPoint(
		ViewportCenter.X - (TextureWidth / 2.0f),
		ViewportCenter.Y - (TextureHeight / 2.0f)
	);

	// Texture 洹몃━湲?
	DrawTexture(InTexture, TextureDrawPoint.X, TextureDrawPoint.Y, TextureWidth, TextureHeight, 0.0f, 0.0f, 1.0f, 1.0f, CrosshairColor);
}


void AXZHUD::UpdateHPBarWidget(float MaxHP, float CurrentHP)
{
	const float NewPercent = FMath::Clamp((CurrentHP / MaxHP), 0.0f, 1.0f);
	HpBarWidget->UpdateHpBar(NewPercent);
}

