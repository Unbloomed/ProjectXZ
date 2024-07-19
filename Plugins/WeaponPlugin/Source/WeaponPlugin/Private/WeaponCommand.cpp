#include "WeaponCommand.h"

#include "LevelEditor.h"

FWeaponCommands::FWeaponCommands()
	: TCommands(TEXT("WeaponPlugin"), NSLOCTEXT("Contexts", "WeaponPlugin", "WeaponPlugin Plugin"), NAME_None, FWeaponStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

FWeaponCommands::~FWeaponCommands()
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
#define LOCTEXT_NAMESPACE "FWeaponPluginModule"
	UI_COMMAND(PluginAction, "WeaponPlugin", "Execute WeaponPlugin action", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
}

void FWeaponCommands::Startup()
{
}
