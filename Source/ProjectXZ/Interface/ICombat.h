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

	virtual void Fire(const FVector_NetQuantize& HitLocation, const FName& MuzzleSocketName) = 0;
};
