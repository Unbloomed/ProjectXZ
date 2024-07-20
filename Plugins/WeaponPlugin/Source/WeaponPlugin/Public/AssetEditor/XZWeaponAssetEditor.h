#pragma once
#include "CoreMinimal.h"
#include "XZWeaponLeftArea.h"
#include "Toolkits/AssetEditorToolkit.h"

/** Slate UI 클래스
 *  LeftArea, DetailArea를 각각 왼쪽과 오른쪽에 띄움
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

protected:
	bool OnRequestClose() override;

private:
	void Open(FString InAssetName);
	TSharedRef<SDockTab> Spawn_LeftAreaTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs);
	void OnLeftAreaSelectedItem(FWeaponRowDataPtr InRowData);
	
	static TSharedPtr< FXZWeaponAssetEditor > Instance;

	TSharedPtr< XZWeaponLeftArea > LeftArea;
	TSharedPtr< IDetailsView > DetailsView;

	static const FName EditorName;
	static const FName LeftAreaTabId;
	static const FName DetailTabId;
};