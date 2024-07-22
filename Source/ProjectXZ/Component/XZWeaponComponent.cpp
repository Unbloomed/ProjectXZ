#include "XZWeaponComponent.h"
#include "ProjectXZ/Character/XZCharacter.h"

UXZWeaponComponent::UXZWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

TObjectPtr<AXZCharacter> UXZWeaponComponent::GetXZCharacter()
{
	if (IsValid(XZCharacter)) return XZCharacter;

	XZCharacter = Cast<AXZCharacter>(GetOwner());
	return XZCharacter;
}

void UXZWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

}
