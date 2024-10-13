
#include "Player/XZCusomizingPlayerController.h"

AXZCusomizingPlayerController::AXZCusomizingPlayerController()
{
}

void AXZCusomizingPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly UIOnlyInputMode;
	SetInputMode(UIOnlyInputMode);

	bShowMouseCursor = true;
}
