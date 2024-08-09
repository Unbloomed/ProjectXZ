
#include "XZTimerManager.h"

UXZTimerManager::UXZTimerManager()
{

}

void UXZTimerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UXZTimerManager::Deinitialize()
{
	Super::Deinitialize();

}

void UXZTimerManager::SetTimer(FTimerHandle& TimerHandle, float Time, bool bLooping, FTimerDelegate TimerCallback)
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerCallback, Time, bLooping);
    }
}

void UXZTimerManager::ClearTimer(FTimerHandle& TimerHandle)
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
    }
}
