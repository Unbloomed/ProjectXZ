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


/////////////////////////////////////////////////////////////////////////////// Start
//////////////////////////////// 로그인 관련 ///////////////////////////////////

void AProjectXZGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* AProjectXZGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	return NewPlayerController;
}

void AProjectXZGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AProjectXZGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ClientConnections.Num() == 0)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("No Client Connection"));
		}
		else
		{
			for (const auto& Connection : NetDriver->ClientConnections)
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Client Connection: %s"), *Connection->GetName());
			}
		}
	}
}

//////////////////////////////// 로그인 관련 ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////// End

