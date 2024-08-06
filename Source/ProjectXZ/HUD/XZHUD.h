#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "XZHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API AXZHUD : public AHUD
{
	GENERATED_BODY()

public:
	AXZHUD();
	virtual void DrawHUD() override;

	// TODO: CrosshairTexture2D 변수위치 이동
	UPROPERTY()
	TObjectPtr<UTexture2D> CrosshairTexture2D;

protected:
	void BeginPlay() override;

private:
	void DrawCrosshair(UTexture2D* InTexture, FVector2D ViewportCenter, FLinearColor CrosshairColor);

	// Test
	void UpdateHPBarWidget(float MaxHP, float CurrentHP);

private:
	TSubclassOf<class UXZHpBarWidget> HpBarWidgetClass;
	TObjectPtr<class UXZHpBarWidget> HpBarWidget;
};
