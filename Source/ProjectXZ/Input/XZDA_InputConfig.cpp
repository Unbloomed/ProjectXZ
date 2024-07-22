#include "XZDA_InputConfig.h"

UXZDA_InputConfig::UXZDA_InputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UXZDA_InputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FXZInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Can't find Input Tag. Check UXZDA_InputConfig::FindNativeInputActionForTag"));

	return nullptr;
}

const UInputAction* UXZDA_InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FXZInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Can't find Input Tag. Check UXZDA_InputConfig::FindAbilityInputActionForTag"));

	return nullptr;
}
