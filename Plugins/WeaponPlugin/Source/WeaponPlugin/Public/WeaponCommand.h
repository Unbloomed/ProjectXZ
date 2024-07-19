#pragma once
#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "WeaponStyle.h"

class FWeaponCommand : public TCommands<FWeaponCommand>
{
public:
	FWeaponCommands();
	~FWeaponCommands();

	FWeaponCommand()
		: TCommands<FWeaponCommand>(TEXT("WeaponPlugin"), NSLOCTEXT("Contexts", "WeaponPlugin", "WeaponPlugin Plugin"), NAME_None, FWeaponStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;
	//*****************************************************

	void Startup();

	TSharedPtr< FUICommandList > Command;
	TSharedPtr< FUICommandInfo > PluginAction;

private:
	TSharedPtr< FExtender > Extender;

};

