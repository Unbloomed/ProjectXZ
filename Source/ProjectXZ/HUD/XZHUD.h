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

	// Test
	void UpdateHPBarWidget(float CurrentHP, float MaxHP);
	FORCEINLINE TObjectPtr<class UXZTimerWidget> GetRespawnTimerWidget() const { return RespawnTimerWidget; }

protected:
	virtual void BeginPlay() override;


private:
	void DrawCrosshair(UTexture2D* InTexture, FVector2D ViewportCenter, FLinearColor CrosshairColor);

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> CharacterOverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> CharacterOverlayWidget;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UXZHpBarWidget> HpBarWidgetClass;
	UPROPERTY()
	TObjectPtr<class UXZHpBarWidget> HpBarWidget;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UXZTimerWidget> RespawnTimerWidgetClass;
	UPROPERTY()
	TObjectPtr<class UXZTimerWidget> RespawnTimerWidget;
};
