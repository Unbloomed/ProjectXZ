#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	virtual void BeginPlay() override;

	// TODO: CrosshairTexture2D º¯¼öÀ§Ä¡ ÀÌµ¿
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Texture")
	TObjectPtr<UTexture2D> CrosshairTexture2D;


protected:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Widget")
	TSubclassOf<UUserWidget> CharacterOverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> CharacterOverlayWidget;


private:
	void DrawCrosshair(UTexture2D* InTexture, FVector2D ViewportCenter, FLinearColor CrosshairColor);

	// Test
	void UpdateHPBarWidget(float MaxHP, float CurrentHP);

private:
	TSubclassOf<class UXZHpBarWidget> HpBarWidgetClass;
	TObjectPtr<class UXZHpBarWidget> HpBarWidget;
};
