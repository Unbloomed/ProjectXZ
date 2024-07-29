#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "XZAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UXZAnimInstance(const FObjectInitializer& ObjectInitializer);

	//virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);

protected:

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif // WITH_EDITOR

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	//UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	//FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

	UPROPERTY(BlueprintReadOnly, Category = "Character State Data")
	float GroundDistance = -1.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Type Tag")
	TMap<FGameplayTag, int> WeaponTypeTag;
};
