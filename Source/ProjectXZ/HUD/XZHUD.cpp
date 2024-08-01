#include "XZHUD.h"

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
