#include "WeaponComponent.h"
#include "ProjectXZ/Character/XZCharacter.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TObjectPtr<AXZCharacter> UWeaponComponent::GetXZCharacter()
{
	if (IsValid(XZCharacter)) return XZCharacter;

	XZCharacter = Cast<AXZCharacter>(GetOwner());
	return XZCharacter;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

