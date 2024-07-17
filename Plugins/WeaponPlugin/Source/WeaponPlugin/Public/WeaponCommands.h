#pragma once
#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "WeaponStyle.h"

class FWeaponCommands : public TCommands<FWeaponCommands>
{
public:

	FWeaponCommands()
		: TCommands<FWeaponCommands>(TEXT("WeaponPlugin"), NSLOCTEXT("Contexts", "WeaponPlugin", "WeaponPlugin Plugin"), NAME_None, FWeaponStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
