// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectXZGameMode.h"
#include "ProjectXZCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectXZGameMode::AProjectXZGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
