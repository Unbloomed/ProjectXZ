
#include "XZCheatManager.h"
#include "GameFramework/Pawn.h"
#include "Character/XZPlayerController.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Console.h"
#include "GameFramework/HUD.h"
#include "GamePlayTag/XZGameplayTags.h"
#include "Component/XZStatComponent.h"
#include "Character/XZPawnExtensionComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(XZCheatManager)

DEFINE_LOG_CATEGORY(LogXZCheat);

/*
	GetTarget은 카메라 위치, 회전에서 LineTraceSingleByChannel를 쏴서 Trace되는 Actor를 return 합니다.
*/

namespace XZCheat
{
	static const FName NAME_Fixed = FName(TEXT("Fixed"));

	static bool bEnableDebugCameraCycling = false;
	static FAutoConsoleVariableRef CVarEnableDebugCameraCycling(
		TEXT("XZCheat.EnableDebugCameraCycling"),
		bEnableDebugCameraCycling,
		TEXT("If true then you can cycle the debug camera while running the game."),
		ECVF_Cheat);

	static bool bStartInGodMode = false;
	static FAutoConsoleVariableRef CVarStartInGodMode(
		TEXT("XZCheat.StartInGodMode"),
		bStartInGodMode,
		TEXT("If true then the God cheat will be applied on begin play"),
		ECVF_Cheat);
};

UXZCheatManager::UXZCheatManager()
{
}

void UXZCheatManager::InitCheatManager()
{
	Super::InitCheatManager();
#if WITH_EDITOR
	if (GIsEditor)
	{
		// 자동 치트 실행 기능
		// APlayerController* PC = GetOuterAPlayerController();
		// for (const FXZCheatToRun& CheatRow : GetDefault<UXZDeveloperSettings>()->CheatsToRun)
		// {
		// 	if (CheatRow.Phase == ECheatExecutionTime::OnCheatManagerCreated)
		// 	{
		// 		PC->ConsoleCommand(CheatRow.Cheat,  /*bWriteToLog=*/ true);
		// 	}
		// }
	}
#endif
}

void UXZCheatManager::CheatOutputText(const FString& TextToOutput)
{
#if USING_CHEAT_MANAGER
	// Output to the console.
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->ViewportConsole)
	{
		GEngine->GameViewport->ViewportConsole->OutputText(TextToOutput);
	}

	// Output to log.
	UE_LOG(LogXZCheat, Display, TEXT("%s"), *TextToOutput);
#endif // USING_CHEAT_MANAGER
}

void UXZCheatManager::Cheat(const FString& Msg)
{
	if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(GetOuterAPlayerController()))
	{
		XZPC->ServerCheat(Msg.Left(128));
	}
}

void UXZCheatManager::CheatAll(const FString& Msg)
{
	if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(GetOuterAPlayerController()))
	{
		XZPC->ServerCheatAll(Msg.Left(128));
	}
}

void UXZCheatManager::DamageSelf(float DamageAmount)
{
	if (UXZStatComponent* StatComponent = GetStatComponent(GetOuterAPlayerController()))
	{
		StatComponent->DecreaseHealth(DamageAmount);
	}
}

void UXZCheatManager::DamageTarget(float DamageAmount)
{
	if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(GetOuterAPlayerController()))
	{
		if (XZPC->GetNetMode() == NM_Client)
		{
			// Automatically send cheat to server for convenience.
			XZPC->ServerCheat(FString::Printf(TEXT("DamageTarget %.2f"), DamageAmount));
			return;
		}

		FHitResult TargetHitResult;
		if (AActor* TargetActor = GetTarget(XZPC, TargetHitResult))
		{
			if (AXZCharacter* TargetCharacter = Cast< AXZCharacter>(TargetActor))
			{
				if (UXZStatComponent* StatComponent = GetStatComponent(TargetCharacter))
				{
					StatComponent->DecreaseHealth(DamageAmount);
				}
			}
		}
	}
}

void UXZCheatManager::HealSelf(float HealAmount)
{
	if (UXZStatComponent* StatComponent = GetStatComponent(GetOuterAPlayerController()))
	{
		StatComponent->IncreaseHealth(HealAmount);
	}
}

void UXZCheatManager::HealTarget(float HealAmount)
{
	if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(GetOuterAPlayerController()))
	{
		FHitResult TargetHitResult;
		AActor* TargetActor = GetTarget(XZPC, TargetHitResult);
		if (TargetActor)
		{
			if (AXZCharacter* TargetCharacter = Cast< AXZCharacter>(TargetActor))
			{
				if (UXZStatComponent* StatComponent = GetStatComponent(TargetCharacter))
				{
					StatComponent->IncreaseHealth(HealAmount);
				}
			}
		}
	}
}

void UXZCheatManager::UnlimitedHealth(int32 Enabled)
{
	// if (ULyraAbilitySystemComponent* LyraASC = GetPlayerAbilitySystemComponent())
	// {
	// 	const FGameplayTag Tag = LyraGameplayTags::Cheat_UnlimitedHealth;
	// 	const bool bHasTag = LyraASC->HasMatchingGameplayTag(Tag);
	// 
	// 	if ((Enabled == -1) || ((Enabled > 0) && !bHasTag) || ((Enabled == 0) && bHasTag))
	// 	{
	// 		if (bHasTag)
	// 		{
	// 			LyraASC->RemoveDynamicTagGameplayEffect(Tag);
	// 		}
	// 		else
	// 		{
	// 			LyraASC->AddDynamicTagGameplayEffect(Tag);
	// 		}
	// 	}
	// }
}

void UXZCheatManager::CheatTest()
{
	UE_LOG(LogTemp, Warning, TEXT("Custom Cheat Activated!"));
}

UXZStatComponent* UXZCheatManager::GetStatComponent(const AXZCharacter* Character) const 
{
	if (Character) 
	{
		return Character->GetStatComponent();
	}

	return nullptr;
}

UXZStatComponent* UXZCheatManager::GetStatComponent(APlayerController* PC) const
{
	if (PC) 
	{
		if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(PC))
		{
			if (AXZCharacter* XZCharacter = Cast<AXZCharacter>(XZPC->GetPawn()))
			{
				return XZCharacter->GetStatComponent();
			}
		}
	}
	
	return nullptr;
}
