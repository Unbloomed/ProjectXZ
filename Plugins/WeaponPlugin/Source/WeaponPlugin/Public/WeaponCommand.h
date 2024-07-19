#pragma once
#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "WeaponStyle.h"

class FWeaponCommand : public TCommands<FWeaponCommand>
{
public:
	FWeaponCommand();
	~FWeaponCommand();

	// TCommands<> interface
	virtual void RegisterCommands() override;
	//*****************************************************

	void Startup();

	TSharedPtr< FUICommandList > Command;
	TSharedPtr< FUICommandInfo > PluginAction;

private:
	TSharedPtr< FExtender > Extender;

};

