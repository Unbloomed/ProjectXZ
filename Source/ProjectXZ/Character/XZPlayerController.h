#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XZPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API AXZPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	AXZPlayerController();
	
protected:
	virtual void PostNetInit() override;
	virtual void OnPossess(APawn* InPawn) override;
};
