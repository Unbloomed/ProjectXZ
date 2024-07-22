#include "WeaponStyle.h"
#include "WeaponModule.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FWeaponStyle::StyleInstance = nullptr;

void FWeaponStyle::Initialize()
{
	if (false == StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FWeaponStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FWeaponStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("WeaponPluginStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FWeaponStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("WeaponPluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("WeaponPlugin")->GetBaseDir() / TEXT("Resources"));

	Style->Set("WeaponPlugin.PluginAction", new IMAGE_BRUSH(TEXT("WeaponButtonIcon"), Icon20x20));
	return Style;
}

void FWeaponStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FWeaponStyle::Get()
{
	return *StyleInstance;
}
