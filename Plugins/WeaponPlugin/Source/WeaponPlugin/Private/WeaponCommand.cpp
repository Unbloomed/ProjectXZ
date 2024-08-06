#include "WeaponCommand.h"
#include "LevelEditor.h"

FWeaponCommand::FWeaponCommand()
	: TCommands(TEXT("WeaponPlugin"), NSLOCTEXT("Contexts", "WeaponPlugin", "WeaponPlugin Plugin"), NAME_None, FWeaponStyle::GetStyleSetName())
{
	// �𸮾� ������ Window �޴��� FUICommandList ���·� ����
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
	// �𸮾� ������ Window �޴��� ����� �� �̸�(="WeaponPlugin")�� ����(="Execute WeaponPlugin action") ����
#define LOCTEXT_NAMESPACE "FWeaponPluginModule"
	UI_COMMAND(PluginAction, "WeaponPlugin", "Execute WeaponPlugin action", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
}

void FWeaponCommand::Startup()
{
}
