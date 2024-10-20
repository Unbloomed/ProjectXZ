#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD/XZHUDBase.h"
#include "XZHUD.generated.h"

/**
 * 
 */
class UXZInventoryWindow;
class UXZInGameLayer;

UCLASS()
class PROJECTXZ_API AXZHUD : public AXZHUDBase
{
	GENERATED_BODY()

public:
	AXZHUD();

	// void UpdateHPBarWidget(float CurrentHP, float MaxHP);
	// FORCEINLINE TObjectPtr<class UXZTimerWidget> GetRespawnTimerWidget() const { return RespawnTimerWidget; }

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OpenInventoryWindow();

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Window", meta = ( AllowPrivateAccess = true ))
	TSubclassOf<UXZInventoryWindow> InventoryWindowClass;
	TObjectPtr<UXZInventoryWindow> InventoryWindow;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Layer", meta = ( AllowPrivateAccess = true ))
	TSubclassOf<UXZInGameLayer> InGameLayerClass;
	TObjectPtr<UXZInGameLayer> InGameLayer;

};
