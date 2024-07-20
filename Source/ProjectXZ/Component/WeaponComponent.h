#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AXZCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	TObjectPtr<AXZCharacter> GetXZCharacter();

protected:
	virtual void BeginPlay() override;


private:
	TObjectPtr<AXZCharacter> XZCharacter;
};
