#include "XZStateComponent.h"
#include "Net/UnrealNetwork.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "Character/XZCharacter.h"
#include "Character/XZCharacter.h"

UXZStateComponent::UXZStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentState = FXZTags::GetXZTags().StateTag_Alive_Posture_Idle;
}


void UXZStateComponent::BeginPlay()
{
	Super::BeginPlay();
	// :: AnimInstance Bind 
	// Cast<UXZAnimInstnace>(GetOwner<ACharacter>()->GetMesh()->GetAnimInstance())
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
	OnChangeState();
}

void UXZStateComponent::OnChangeState()
{
	OnStateChanged.Broadcast(CurrentState);
}
