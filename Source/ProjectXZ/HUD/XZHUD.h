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
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

	// TODO: CrosshairTexture2D 변수위치 이동
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Texture")
	TObjectPtr<UTexture2D> CrosshairTexture2D;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Widget")
	TSubclassOf<UUserWidget> CharacterOverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> CharacterOverlayWidget;

private:
	void DrawCrosshair(UTexture2D* InTexture, FVector2D ViewportCenter, FLinearColor CrosshairColor);
};
