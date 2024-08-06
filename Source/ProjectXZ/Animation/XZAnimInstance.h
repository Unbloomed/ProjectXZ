// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "XZAnimInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EBlendSpaceMode : uint8
{
	None = 0,
	Idle,
	crouch,
	aim,
	shoulder
};

class UXZStateComponent;

UCLASS()
class PROJECTXZ_API UXZAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, EBlendSpaceMode> MatchingTagEnumMap;

	UPROPERTY()
	EBlendSpaceMode CurrentState;

	//UFUNCTION()
	//void PlayAnimMontageFromMontage(UAnimMontage* Montage);

	UFUNCTION()
	EBlendSpaceMode GetEnumFromTag(FGameplayTag Tag);

public:
	UFUNCTION()
	void PlayMontageWithTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	void SetCurrentState(EBlendSpaceMode Enum) { CurrentState = Enum; }

	UFUNCTION(BlueprintCallable)
	EBlendSpaceMode GetCurrentState() { return CurrentState; }

protected:
	UPROPERTY()
	TObjectPtr<UXZStateComponent> StateComponent;
};
