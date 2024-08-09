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
	
public:
	AXZPlayerController();
	
	/////////////////// Cheat ///////////////////
	// Run a cheat command on the server.
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerCheat(const FString& Msg);
	// Run a cheat command on the server for all players.
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerCheatAll(const FString& Msg);
	virtual void AddCheats(bool bForce) override;
	// virtual void UpdateForceFeedback(IInputInterface* InputInterface, const int32 ControllerId) override;
	// bool ShouldAlwaysPlayForceFeedback() const;
	/////////////////////////////////////////////////
protected:
	virtual void PostNetInit() override;
	virtual void OnPossess(APawn* InPawn) override;
};
