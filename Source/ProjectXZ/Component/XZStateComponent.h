#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XZStateComponent.generated.h"

/*
enum class ECharacterState : uint8
{
	Default,
	Aim,
	Fire
};
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZStateComponent();

protected:
	virtual void BeginPlay() override;
};
