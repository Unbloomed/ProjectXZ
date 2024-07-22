#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "XZAssetManager.generated.h"

/**
 * 
 */

UCLASS()
class PROJECTXZ_API UXZAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UXZAssetManager& GetXZAssetManager();

protected:
	virtual void StartInitialLoading() override;
};
