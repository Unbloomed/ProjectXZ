#include "AssetEditor/XZWeaponAssetEditor.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"

const FName FXZWeaponAssetEditor::EditorName = "WeaponAssetEditor";
const FName FXZWeaponAssetEditor::ListViewTabId = "ListView";
const FName FXZWeaponAssetEditor::DetailTabId = "Details";

TSharedPtr< FXZWeaponAssetEditor > FXZWeaponAssetEditor::Instance = nullptr;

void FXZWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FXZWeaponAssetEditor());
	Instance->Open(InAssetName);
}

void FXZWeaponAssetEditor::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}
}

void FXZWeaponAssetEditor::Open(FString InAssetName)
{
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.175f)
					->AddTab(ListViewTabId, ETabState::OpenedTab)//ListViewTabId
					->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.725f)
					->AddTab(DetailTabId, ETabState::OpenedTab)//DetailTabId
					->SetHideTabWell(true)
				)
			)
		);

	UXZDA_Weapon* asset = NewObject<UXZDA_Weapon>();
	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EditorName, layout, true, true, asset);

}

void FXZWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab;
	tab.BindSP(this, &FXZWeaponAssetEditor::Spawn_ListViewTab);
	TabManager->RegisterTabSpawner(ListViewTabId, tab);
}

TSharedRef<SDockTab> FXZWeaponAssetEditor::Spawn_ListViewTab(const FSpawnTabArgs& InArgs)
{
	TSharedPtr<SDockTab> tab = SNew(SDockTab)
		[
			SNew(SButton)
				.OnClicked(this, &FXZWeaponAssetEditor::OnClicked)
				[
					SNew(STextBlock)
						.Text(FText::FromString("Test"))
				]
		];

	return tab.ToSharedRef();

	//return SNew(SDockTab);
}

FName FXZWeaponAssetEditor::GetToolkitFName() const
{
	return EditorName;
}

FText FXZWeaponAssetEditor::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FXZWeaponAssetEditor::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();
}

FLinearColor FXZWeaponAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}

FReply FXZWeaponAssetEditor::OnClicked()
{
	GLog->Log("Test");

	return FReply::Handled();
}