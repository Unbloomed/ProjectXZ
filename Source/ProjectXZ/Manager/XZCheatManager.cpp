
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

// 치트 명령어를 처리하는 함수
void UXZCheatManager::Cheat(const FString& Msg)
{
	if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(GetOuterAPlayerController()))
	{
		// 서버에 치트 명령어를 전송
		XZPC->ServerCheat(Msg.Left(128));
	}
}

// 모든 플레이어에게 치트 명령어를 전송하는 함수
void UXZCheatManager::CheatAll(const FString& Msg)
{
	if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(GetOuterAPlayerController()))
	{
		// 서버에 모든 플레이어에게 치트 명령어를 전송한다.
		XZPC->ServerCheatAll(Msg.Left(128));
	}
}

// 자기 자신에게 피해를 주는 함수
void UXZCheatManager::DamageSelf(float DamageAmount)
{
	if (UXZStatComponent* StatComponent = GetStatComponent(GetOuterAPlayerController()))
	{
		// 체력을 감소
		StatComponent->DecreaseHealth(DamageAmount);
	}
}

// 타겟에게 피해를 주는 함수
void UXZCheatManager::DamageTarget(float DamageAmount)
{
	if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(GetOuterAPlayerController()))
	{
		if (XZPC->GetNetMode() == NM_Client)
		{
			// 클라이언트일 경우 자동으로 서버에 치트 명령어를 전송
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
					// 타겟의 체력을 감소
					StatComponent->DecreaseHealth(DamageAmount);
				}
			}
		}
	}
}

// 자기 자신을 치유하는 함수
void UXZCheatManager::HealSelf(float HealAmount)
{
	if (UXZStatComponent* StatComponent = GetStatComponent(GetOuterAPlayerController()))
	{
		// 체력을 회복
		StatComponent->IncreaseHealth(HealAmount);
	}
}

// 타겟을 치유하는 함수
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
					// 타겟의 체력을 회복
					StatComponent->IncreaseHealth(HealAmount);
				}
			}
		}
	}
}

void UXZCheatManager::UnlimitedHealth(int32 Enabled)
{

}

void UXZCheatManager::CheatTest()
{
	UE_LOG(LogTemp, Warning, TEXT("Custom Cheat Activated!"));
}

// 캐릭터에서 StatComponent를 가져오는 함수
UXZStatComponent* UXZCheatManager::GetStatComponent(const AXZCharacter* Character) const 
{
	if (Character) 
	{
		// 캐릭터에서 StatComponent를 반환
		return Character->GetStatComponent();
	}

	// 캐릭터가 없을 경우 nullptr을 반환
	return nullptr;
}

// 플레이어 컨트롤러에서 StatComponent를 가져오는 함수
UXZStatComponent* UXZCheatManager::GetStatComponent(APlayerController* PC) const
{
	if (PC) 
	{
		if (AXZPlayerController* XZPC = Cast<AXZPlayerController>(PC))
		{
			if (AXZCharacter* XZCharacter = Cast<AXZCharacter>(XZPC->GetPawn()))
			{
				// 플레이어 컨트롤러의 포운에서 StatComponent를 반환
				return XZCharacter->GetStatComponent();
			}
		}
	}
	
	// 플레이어 컨트롤러가 없거나 StatComponent를 찾을 수 없을 경우 nullptr을 반환
	return nullptr;
}
