#include "Component/XZInventoryComponent.h"
#include "GameplayTag/XZGameplayTags.h"
#include "Net/UnrealNetwork.h"

UXZInventoryComponent::UXZInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UXZInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}

void UXZInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

