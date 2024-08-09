#include "Prop/XZSpawnPoint.h"

AXZSpawnPoint::AXZSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
}
