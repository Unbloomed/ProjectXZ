#include "AssetEditor/XZWeaponAssetEditor.h"
#include "AssetEditor/XZWeaponLeftArea.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"

const FName FXZWeaponAssetEditor::EditorName = "WeaponAssetEditor";
const FName FXZWeaponAssetEditor::LeftAreaTabId = "LeftArea";
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

// 창이 닫힐 때 콜이 되게 설계.
bool FXZWeaponAssetEditor::OnRequestClose()
{
	if (LeftArea.IsValid())
	{
		LeftArea.Reset();
	}

	if (DetailsView.IsValid())
	{
		// AssetEditorSubsystem안에(=DetailView안에) GetEditingObject()가 등록되어 있었다면 해제하고 Editor에 알린다.
		if (IsValid(GEditor) && IsValid(GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()))
		{
			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(GetEditingObject(), this);
		}

		DetailsView.Reset();
	}

	return true; // true 리턴(=창 닫힘), false 리턴(= 창이 닫힐 수 없음)
}

void FXZWeaponAssetEditor::Open(FString InAssetName)
{
	//**************************************************************************************
	//** LeftArea
	//	 XZWeaponLeftArea에서 받은 자료형을 생성하여 넣어준다.
	LeftArea = SNew(XZWeaponLeftArea) 
		.WeaponSelectedItem(this, &FXZWeaponAssetEditor::OnLeftAreaSelectedItem); //LeftArea에서 선택한 데이터
	//**************************************************************************************

	//**************************************************************************************
	//** DetailsView
	FPropertyEditorModule& Prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs Args(false, false, true, FDetailsViewArgs::HideNameArea);
	Args.ViewIdentifier = "WeaponAssetEditorDetailsView"; //식별자 설정. 게임 Editor쪽에서 DetailView 접근시 이 식별자로 찾을 수 있다.

	DetailsView = Prop.CreateDetailView(Args);
	//**************************************************************************************

	//**************************************************************************************
	//**  Layout 설정
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.175f) // 왼쪽 17.5% 사용
					->AddTab(LeftAreaTabId, ETabState::OpenedTab) // LeftAreaTabId
					->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.725f) // 오른쪽 72.5% 사용
					->AddTab(DetailTabId, ETabState::OpenedTab) // DetailTabId
					->SetHideTabWell(true)
				)
			)
		);
	//**************************************************************************************

	UXZDA_Weapon* DA_Weapon = LeftArea->GetFirstDataPtr()->DA_Weapon; // LeftArea의 맨 위 첫번째 데이터 선택

	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EditorName, Layout, true, true, DA_Weapon);

	LeftArea->SelectedDataAsset(DA_Weapon);
}

void FXZWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab Tab_LeftArea;
	Tab_LeftArea.BindSP(this, &FXZWeaponAssetEditor::Spawn_LeftAreaTab);
	TabManager->RegisterTabSpawner(LeftAreaTabId, Tab_LeftArea);

	FOnSpawnTab Tab_DetailsView;
	Tab_DetailsView.BindSP(this, &FXZWeaponAssetEditor::Spawn_DetailsViewTab);
	TabManager->RegisterTabSpawner(DetailTabId, Tab_DetailsView);
}

TSharedRef<SDockTab> FXZWeaponAssetEditor::Spawn_LeftAreaTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			LeftArea.ToSharedRef()
		];
}

TSharedRef<SDockTab> FXZWeaponAssetEditor::Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
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

void FXZWeaponAssetEditor::OnLeftAreaSelectedItem(FWeaponRowDataPtr InRowData)
{
	if (nullptr == InRowData) return; // LeftArea에서 선택한게 없다면(또는 빈 공간을 선택했다면)

	if (IsValid(GetEditingObject())) // 편집하는 객체가 있다면
	{
		RemoveEditingObject(GetEditingObject()); // 현재 창에서 편집중인 애들 제거
	}

	AddEditingObject(InRowData->DA_Weapon);		 // 현재 창에 편집해줄 객체를 등록
	DetailsView->SetObject(InRowData->DA_Weapon);// 창 안의 DetailsView도 변경
}
