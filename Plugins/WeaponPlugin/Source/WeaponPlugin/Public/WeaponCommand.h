#pragma once
#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "WeaponStyle.h"

class FWeaponCommand : public TCommands<FWeaponCommand>
{
public:

	FWeaponCommand()
		: TCommands<FWeaponCommand>(TEXT("WeaponPlugin"), NSLOCTEXT("Contexts", "WeaponPlugin", "WeaponPlugin Plugin"), NAME_None, FWeaponStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
