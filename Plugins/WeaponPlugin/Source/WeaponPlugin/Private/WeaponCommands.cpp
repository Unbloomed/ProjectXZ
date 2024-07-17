#include "WeaponCommands.h"

#define LOCTEXT_NAMESPACE "FWeaponPluginModule"

void FWeaponCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "WeaponPlugin", "Execute WeaponPlugin action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
