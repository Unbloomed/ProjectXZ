#include "XZPlayerController.h"


AXZPlayerController::AXZPlayerController()
{
	bReplicates = true;
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
