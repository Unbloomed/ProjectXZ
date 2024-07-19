#include "WeaponCommand.h"

#define LOCTEXT_NAMESPACE "FWeaponPluginModule"

void FWeaponCommand::RegisterCommands()
{
	UI_COMMAND(PluginAction, "WeaponPlugin", "Execute WeaponPlugin action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
