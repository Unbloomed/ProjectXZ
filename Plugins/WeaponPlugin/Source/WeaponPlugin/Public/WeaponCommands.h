#pragma once
#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "WeaponStyle.h"

class FWeaponCommands : public TCommands<FWeaponCommands>
{
public:
	FWeaponCommands();
	~FWeaponCommands();

	//*****************************************************
	//** TCommands<> interface
	virtual void RegisterCommands() override;
	//*****************************************************

	void Startup();

	TSharedPtr< FUICommandList > Command;
	TSharedPtr< FUICommandInfo > PluginAction;

private:
	TSharedPtr< FExtender > Extender;

};

