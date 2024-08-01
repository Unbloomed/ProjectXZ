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
	virtual void DrawHUD() override;

	// TODO: CrosshairTexture2D 변수위치 이동
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> CrosshairTexture2D;

private:
	void DrawCrosshair(UTexture2D* InTexture, FVector2D ViewportCenter, FLinearColor CrosshairColor);
};
