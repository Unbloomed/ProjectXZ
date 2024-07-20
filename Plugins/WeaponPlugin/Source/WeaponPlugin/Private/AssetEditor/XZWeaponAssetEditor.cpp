#include "AssetEditor/XZWeaponAssetEditor.h"
#include "AssetEditor/XZWeaponLeftArea.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"

const FName FXZWeaponAssetEditor::EditorName = "WeaponAssetEditor";
const FName FXZWeaponAssetEditor::ListViewTabId = "ListView";
const FName FXZWeaponAssetEditor::DetailTabId = "Details";

TSharedPtr< FXZWeaponAssetEditor > FXZWeaponAssetEditor::Instance = nullptr;

void FXZWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	if (Instance.IsValid())
	{
		Instance->OnClose();

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
		Instance->OnClose();

		Instance.Reset();
		Instance = nullptr;
	}
}

void FXZWeaponAssetEditor::Open(FString InAssetName)
{
	LeftArea = SNew(XZWeaponLeftArea); // XZWeaponLeftArea에서 받은 자료형을 생성하여 넣어준다.

	// Layout 설정
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			//->Split // 위
			//(
			//	FTabManager::NewStack()
			//	->SetSizeCoefficient(0.1f) // 10% 사용
			//	//->AddTab(GetToolbarTabId(), ETabState::OpenedTab) // depreciated
			//	->AddTab(GetEditingAssetTypeName(), ETabState::OpenedTab)
			//)
			->Split // 아래
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.175f) // 왼쪽 17.5% 사용
					->AddTab(ListViewTabId, ETabState::OpenedTab)//ListViewTabId
					->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.725f) // 오른쪽 72.5% 사용
					->AddTab(DetailTabId, ETabState::OpenedTab)//DetailTabId
					->SetHideTabWell(true)
				)
			)
		);

	UXZDA_Weapon* XZDA_Weapon = NewObject<UXZDA_Weapon>();
	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EditorName, Layout, true, true, XZDA_Weapon);

}

void FXZWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab Tab;
	Tab.BindSP(this, &FXZWeaponAssetEditor::Spawn_ListViewTab);
	TabManager->RegisterTabSpawner(ListViewTabId, Tab);
}

TSharedRef<SDockTab> FXZWeaponAssetEditor::Spawn_ListViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			LeftArea.ToSharedRef()
		];
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