#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

/** Slate UI Å¬·¡½º
 * 
 */

class WEAPONPLUGIN_API FXZWeaponAssetEditor : public FAssetEditorToolkit
{

public:
	static void OpenWindow(FString InAssetName = "");
	static void Shutdown();
	
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	FName GetToolkitFName() const override;
	FText GetBaseToolkitName() const override;
	FString GetWorldCentricTabPrefix() const override;
	FLinearColor GetWorldCentricTabColorScale() const override;

private:
	void Open(FString InAssetName);
	TSharedRef<SDockTab> Spawn_ListViewTab(const FSpawnTabArgs& InArgs);
	FReply OnClicked();
	
	static TSharedPtr< FXZWeaponAssetEditor > Instance;
	static const FName EditorName;
	static const FName ListViewTabId;
	static const FName DetailTabId;

	TSharedPtr< class XZWeaponLeftArea > LeftArea;
};