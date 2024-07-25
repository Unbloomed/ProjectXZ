#include "XZAnimInstance.h"
#include "ProjectXZ/Character/XZCharacter.h"
#include "ProjectXZ/Character/XZCharacterMovementComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(XZAnimInstance)


UXZAnimInstance::UXZAnimInstance(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{

}

//void UXZAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
//{
//	check(ASC);
//
//	GameplayTagPropertyMap.Initialize(this, ASC);
//}

#if WITH_EDITOR
EDataValidationResult UXZAnimInstance::IsDataValid(FDataValidationContext& Context) const
{
	Super::IsDataValid(Context);

	//GameplayTagPropertyMap.IsDataValid(this, Context);

	return ((Context.GetNumErrors() > 0) ? EDataValidationResult::Invalid : EDataValidationResult::Valid);
}
#endif // WITH_EDITOR

void UXZAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
}

void UXZAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	const AXZCharacter* Character = Cast<AXZCharacter>(GetOwningActor());
	if (false == IsValid(Character)) return;

	UXZCharacterMovementComponent* CharMoveComp = CastChecked<UXZCharacterMovementComponent>(Character->GetCharacterMovement());
	const FXZCharacterGroundInfo& GroundInfo = CharMoveComp->GetGroundInfo();
	GroundDistance = GroundInfo.GroundDistance;
}


