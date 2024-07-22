#pragma once
//#include "CoreMinimal.h"
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
	void BindNativeActions(const UXZDA_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UXZDA_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);
};

template <class UserClass, typename FuncType>
void UXZInputComponent::BindNativeActions(const UXZDA_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	checkf(InputConfig, TEXT("No InputConfig. Check UXZInputComponent::BindNativeActions()"))

	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UXZInputComponent::BindAbilityActions(const UXZDA_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	checkf(InputConfig, TEXT("No InputConfig. Check UXZInputComponent::BindAbilityActions()"))

	for (const FXZInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered), Object, PressedFunc, Action.InputTag).GetHandle();
			}
			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle());
			}
		}
	}
}


