#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XZWeaponComponent.generated.h"

class AXZCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZWeaponComponent();
	TObjectPtr<AXZCharacter> GetXZCharacter();

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<AXZCharacter> XZCharacter;

};
