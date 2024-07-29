#include "WeaponCommand.h"
#include "LevelEditor.h"

FWeaponCommand::FWeaponCommand()
	: TCommands(TEXT("WeaponPlugin"), NSLOCTEXT("Contexts", "WeaponPlugin", "WeaponPlugin Plugin"), NAME_None, FWeaponStyle::GetStyleSetName())
{
	// 언리얼 에디터 Window 메뉴에 FUICommandList 형태로 생성
	Command = MakeShareable(new FUICommandList());
}

FWeaponCommand::~FWeaponCommand()
{
	if (Command.IsValid())
	{
		Command.Reset();
	}

	if (Extender.IsValid())
	{
		Extender.Reset();
	}
}

void FWeaponCommand::RegisterCommands()
{
	// 언리얼 에디터 Window 메뉴에 노출될 때 이름(="WeaponPlugin")과 설명(="Execute WeaponPlugin action") 설정
#define LOCTEXT_NAMESPACE "FWeaponPluginModule"
	UI_COMMAND(PluginAction, "WeaponPlugin", "Execute WeaponPlugin action", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
}

void FWeaponCommand::Startup()
{
}
