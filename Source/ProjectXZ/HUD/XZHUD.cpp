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

		// Crosshair 그리기
		DrawCrosshair(CrosshairTexture2D, ViewportCenter, FLinearColor::White);
	}
}

void AXZHUD::BeginPlay()
{
	Super::BeginPlay();

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
	const float TextureWidth = InTexture->GetSizeX();  // Texture 너비
	const float TextureHeight = InTexture->GetSizeY(); // Texture 높이

	// Texture 그리기 위치 설정
	const FVector2D TextureDrawPoint(
		ViewportCenter.X - (TextureWidth / 2.0f),
		ViewportCenter.Y - (TextureHeight / 2.0f)
	);

	// Texture 그리기
	DrawTexture(InTexture, TextureDrawPoint.X, TextureDrawPoint.Y, TextureWidth, TextureHeight, 0.0f, 0.0f, 1.0f, 1.0f, CrosshairColor);
}

void AXZHUD::UpdateHPBarWidget(float MaxHP, float CurrentHP)
{
	const float NewPercent = FMath::Clamp((CurrentHP / MaxHP), 0.0f, 1.0f);
	HpBarWidget->UpdateHpBar(NewPercent);
}
