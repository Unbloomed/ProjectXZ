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

	// TODO: CrosshairTexture2D 쨘짱쩌철?짠횆징 ?횑쨉쩔
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Texture")
	TObjectPtr<UTexture2D> CrosshairTexture2D;


protected:
	virtual void BeginPlay() override;


private:
	void DrawCrosshair(UTexture2D* InTexture, FVector2D ViewportCenter, FLinearColor CrosshairColor);

	// Test
	void UpdateHPBarWidget(float MaxHP, float CurrentHP);

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> CharacterOverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> CharacterOverlayWidget;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UXZHpBarWidget> HpBarWidgetClass;
	UPROPERTY()
	TObjectPtr<class UXZHpBarWidget> HpBarWidget;
};
