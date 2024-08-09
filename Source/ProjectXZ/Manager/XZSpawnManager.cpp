#include "Manager/XZSpawnManager.h"
#include "Prop/XZSpawnPoint.h"
#include "EngineUtils.h"

UXZSpawnManager::UXZSpawnManager()
{

}

void UXZSpawnManager::RequestSpawnCharacter(APawn* Pawn, const FGenericTeamId& TeamID)
{
	if (nullptr == Pawn || nullptr == PlayerSpawnPoints.Find(TeamID)) return;

	FVector PlayerLocation = PlayerSpawnPoints[TeamID]->GetActorLocation();
	Pawn->SetActorLocation(PlayerLocation);
}

void UXZSpawnManager::PostInitialize()
{
	Super::PostInitialize();

	if (AXZSpawnPoint::StaticClass())
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(GetWorld(), EGetWorldErrorMode::LogAndReturnNull))
		{
			for (TActorIterator<AXZSpawnPoint> It(World, AXZSpawnPoint::StaticClass()); It; ++It)
			{
				AXZSpawnPoint* SpawnPoint = *It;
				if (SpawnPoint)
				{
					PlayerSpawnPoints.Add(SpawnPoint->GetGenericTeamId(), SpawnPoint);
				}
			}
		}
	}
}
