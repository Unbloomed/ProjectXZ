#include "XZPlayerController.h"
#include "HUD/XZHUD.h"
#include "XZCharacter.h"
#include "Component/XZStatComponent.h"
#include "Manager/XZCheatManager.h"
#include "EngineUtils.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(XZPlayerController)

namespace XZ
{
	namespace Input
	{
		static int32 ShouldAlwaysPlayForceFeedback = 0;
		static FAutoConsoleVariableRef CVarShouldAlwaysPlayForceFeedback(TEXT("XZPC.ShouldAlwaysPlayForceFeedback"),
			ShouldAlwaysPlayForceFeedback,
			TEXT("Should force feedback effects be played, even if the last input device was not a gamepad?"));
	}
}

AXZPlayerController::AXZPlayerController()
{
	bReplicates = true;

	CheatClass = UXZCheatManager::StaticClass();
}

/////////////////////////////////////////////////////////////////////////////// Start
//////////////////////////////// 로그인 관련 ///////////////////////////////////


void AXZPlayerController::PostNetInit()
{
	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();

	if (NetDriver)
	{
		if (NetDriver->ServerConnection)
		{
			UE_LOG(LogTemp, Log, TEXT("Server Connection: %s"), *NetDriver->ServerConnection->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("No NetDriver"));
	}
}

void AXZPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

//////////////////////////////// 로그인 관련 ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////// End

void AXZPlayerController::ServerCheat_Implementation(const FString& Msg)
{
#if USING_CHEAT_MANAGER
	if (CheatManager)
	{
		// UE_LOG(LogXZ, Warning, TEXT("ServerCheat: %s"), *Msg);
		ClientMessage(ConsoleCommand(Msg));
	}
#endif // #if USING_CHEAT_MANAGER
}

bool AXZPlayerController::ServerCheat_Validate(const FString& Msg)
{
	return true;
}

void AXZPlayerController::ServerCheatAll_Implementation(const FString& Msg)
{
#if USING_CHEAT_MANAGER
	if (CheatManager)
	{
		// UE_LOG(LogXZ, Warning, TEXT("ServerCheatAll: %s"), *Msg);
		for (TActorIterator<AXZPlayerController> It(GetWorld()); It; ++It)
		{
			AXZPlayerController* XZPC = (*It);
			if (XZPC)
			{
				XZPC->ClientMessage(XZPC->ConsoleCommand(Msg));
			}
		}
	}
#endif // #if USING_CHEAT_MANAGER
}

bool AXZPlayerController::ServerCheatAll_Validate(const FString& Msg)
{
	return true;
}

void AXZPlayerController::AddCheats(bool bForce)
{
#if USING_CHEAT_MANAGER
	Super::AddCheats(true);
#else //#if USING_CHEAT_MANAGER
	Super::AddCheats(bForce);
#endif // #else //#if USING_CHEAT_MANAGER
}

// bool AXZPlayerController::ShouldAlwaysPlayForceFeedback() const
// {
// 	static const IConsoleVariable* CVarShouldAlwaysPlayForceFeedback = IConsoleManager::Get().FindConsoleVariable(TEXT("XZPC.ShouldAlwaysPlayForceFeedback"));
// 	return CVarShouldAlwaysPlayForceFeedback ? CVarShouldAlwaysPlayForceFeedback->GetBool() : false;
// }
/*
void AXZPlayerController::UpdateForceFeedback(IInputInterface* InputInterface, const int32 ControllerId)
{
	// if (bForceFeedbackEnabled)
	// {
	// 	// if (ShouldAlwaysPlayForceFeedback())
	// 	// {
	// 	// 	InputInterface->SetForceFeedbackChannelValues(ControllerId, ForceFeedbackValues);
	// 	// 	return;
	// 	// }
	// }

	InputInterface->SetForceFeedbackChannelValues(ControllerId, FForceFeedbackValues());
}
*/
