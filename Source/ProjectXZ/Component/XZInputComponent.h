#pragma once
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "ProjectXZ/Input/XZDA_InputConfig.h"
#include "XZInputComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UObject;

/** class: UXZInputComponent 
 *	XZDA_InputConfig를 사용해서 input을 맵핑하는 컴포넌트 클래스
 */

UCLASS()
class PROJECTXZ_API UXZInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UXZInputComponent(const FObjectInitializer& ObjectInitializer);

	template<class UserClass, typename FuncType>
	void BindPressActions(const UXZDA_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	//template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	//void BindPressReleaseActions(const UXZDA_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindPressHeldReleaseActions(const UXZDA_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename FuncType>
void UXZInputComponent::BindPressActions(const UXZDA_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	checkf(InputConfig, TEXT("No InputConfig. Check UXZInputComponent::BindNativeActions()"))

	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}


/*
template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UXZInputComponent::BindPressReleaseActions(const UXZDA_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	checkf(InputConfig, TEXT("No InputConfig. Check UXZInputComponent::BindPressReleaseActions()"))

	for (const 
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, 
			}
		}
	}
}
*/


template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UXZInputComponent::BindPressHeldReleaseActions(const UXZDA_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	checkf(InputConfig, TEXT("No InputConfig. Check UXZInputComponent::BindPressHeldReleaseActions()"))

	for (const FXZInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Ongoing, Object, HeldFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
		}
	}
}

