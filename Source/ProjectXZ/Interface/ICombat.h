#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICombat.generated.h"

class UXZCombatHandler;

UINTERFACE(MinimalAPI)
class UICombat : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class PROJECTXZ_API IICombat
{
	GENERATED_BODY()

public:
	virtual UXZCombatHandler* CreateCombatHandler() = 0;
};
