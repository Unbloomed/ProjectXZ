#include "XZStateComponent.h"
#include "Net/UnrealNetwork.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "Character/XZCharacter.h"
#include "Character/XZCharacter.h"
#include "Animation/XZAnimInstance.h"

UXZStateComponent::UXZStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

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

void UXZStateComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXZStateComponent, CurrentState);
}

void UXZStateComponent::SetState(FGameplayTag NewState)
{
	CurrentState = NewState;
}

void UXZStateComponent::OnRep_CurrentState()
{
	UE_LOG(LogTemp, Log, TEXT("UXZStateComponent::OnRep_CurrentState - Begin!"));
	OnChangeState();
}

void UXZStateComponent::OnChangeState()
{
	UE_LOG(LogTemp, Log, TEXT("UXZStateComponent::OnChangeState - Begin!"));
	OnStateChanged.Broadcast(CurrentState);
}
