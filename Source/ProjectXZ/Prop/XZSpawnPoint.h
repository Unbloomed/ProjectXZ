#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/XZCharacter.h"
#include "XZSpawnPoint.generated.h"

UCLASS()
class PROJECTXZ_API AXZSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AXZSpawnPoint();
    FGenericTeamId GetGenericTeamId() const { return TeamID; }

protected:
	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamID = 0;

private:
	TObjectPtr<USceneComponent> SceneComponent;

};
