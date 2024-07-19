#include "WeaponModule.h"
#include "WeaponStyle.h"
#include "WeaponCommand.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "WeaponContextMenu.h"
#include "AssetEditor/XZWeaponAssetEditor.h"

static const FName WeaponPluginTabName("WeaponPlugin");

#define LOCTEXT_NAMESPACE "FWeaponModule"

IMPLEMENT_MODULE(FWeaponModule, WeaponPlugin) // WeaponPlugin.uplugin�� ��� �̸��� ��ġ

void FWeaponModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FWeaponStyle::Initialize();
	FWeaponStyle::ReloadTextures();

	FWeaponCommand::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type Categories = AssetTools.RegisterAdvancedAssetCategory("DataAsset_Weapon", FText::FromString("WeaponPlugin"));

	ContextMenu = MakeShareable(new FWeaponContextMenu(Categories));
	AssetTools.RegisterAssetTypeActions(ContextMenu.ToSharedRef());
	
	///////////////////////////////////////////////////////////////////////////////////////////
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FWeaponCommand::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FWeaponModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FWeaponModule::RegisterMenus));
	///////////////////////////////////////////////////////////////////////////////////////////
}

void FWeaponModule::ShutdownModule()
{
	if (ContextMenu.IsValid())
	{
		ContextMenu.Reset();
	}
	if (Command.IsValid())
	{
		Command.Reset();
	}

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	FWeaponStyle::Shutdown();

	FWeaponCommand::Unregister();
}

void FWeaponModule::PluginButtonClicked()
{
	FXZWeaponAssetEditor::OpenWindow();
	
}

// Toolbar에 등록
void FWeaponModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FWeaponCommand::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FWeaponCommand::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	