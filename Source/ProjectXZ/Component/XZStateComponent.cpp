#include "XZStateComponent.h"
#include "Net/UnrealNetwork.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "Character/XZCharacter.h"
#include "ProjectXZ.h"
#include "Animation/XZAnimInstance.h"


UXZStateComponent::UXZStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
	CurrentState = FXZTags::GetXZTags().StateTag_Alive_Posture_Idle;
}


void UXZStateComponent::BeginPlay()
{
	Super::BeginPlay();
	// :: AnimInstance Bind 
	AnimInstance = Cast<UXZAnimInstance>(GetOwner<ACharacter>()->GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		OnStateChanged.AddUObject(AnimInstance, &UXZAnimInstance::PlayMontageWithTag);
	}
}

void UXZStateComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetIsReplicated(true);
}

void UXZStateComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXZStateComponent, CurrentState);
}

void UXZStateComponent::SetState(FGameplayTag NewState)
{
	CurrentState = NewState;
	OnChangeState();
	
	const FString NetModeInfo =
		(GetWorld()->GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) : ((GetWorld()->GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER"));

	FString LocalNetModeInfo;
	FString RemoteNetModeInfo;

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		LocalNetModeInfo = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), PC->GetLocalRole());
		RemoteNetModeInfo = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), PC->GetRemoteRole());
	}
	else
	{
		LocalNetModeInfo = TEXT("NO_PLAYER_CONTROLLER");
		RemoteNetModeInfo = TEXT("NO_PLAYER_CONTROLLER");
	}
	UE_LOG(LogTemp, Log, TEXT("UXZStateComponent::SetState / [%s] [%s] [%s]"), *NetModeInfo, *LocalNetModeInfo, *RemoteNetModeInfo);
	// XZ_SUBLOG(LogXZNetwork, Log, TEXT(""));
}

void UXZStateComponent::OnRep_CurrentState()
{
	UE_LOG(LogTemp, Log, TEXT("UXZStateComponent::OnRep_CurrentState - Begin!"));
	OnChangeState();

	const FString NetModeInfo =
		(GetWorld()->GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) : ((GetWorld()->GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER"));

	FString LocalNetModeInfo;
	FString RemoteNetModeInfo;

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		LocalNetModeInfo = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), PC->GetLocalRole());
		RemoteNetModeInfo = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), PC->GetRemoteRole());
	}
	else
	{
		LocalNetModeInfo = TEXT("NO_PLAYER_CONTROLLER");
		RemoteNetModeInfo = TEXT("NO_PLAYER_CONTROLLER");
	}
	UE_LOG(LogTemp, Log, TEXT("UXZStateComponent::OnRep_CurrentState / [%s] [%s] [%s]"), *NetModeInfo, *LocalNetModeInfo, *RemoteNetModeInfo);
}

void UXZStateComponent::OnChangeState()
{
	UE_LOG(LogTemp, Log, TEXT("UXZStateComponent::OnChangeState - Begin!"));
	OnStateChanged.Broadcast(CurrentState);
}
