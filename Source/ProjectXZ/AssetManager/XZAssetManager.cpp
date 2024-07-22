#include "XZAssetManager.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"

UXZAssetManager& UXZAssetManager::GetXZAssetManager()
{
	checkf(GEngine, TEXT("No GEngine. Check UXZAssetManager& UXZAssetManager::GetXZAssetManager()"));

	UXZAssetManager* XZAssetManager = Cast<UXZAssetManager>(GEngine->AssetManager);
	return *XZAssetManager;
}

void UXZAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FXZTags::InitializeNativeGameplayTags();
}
