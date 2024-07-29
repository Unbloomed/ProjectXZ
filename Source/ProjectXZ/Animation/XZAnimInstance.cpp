// Fill out your copyright notice in the Description page of Project Settings.


#include "../Animation/XZAnimInstance.h"
#include "../GameplayTag/XZGameplayTags.h"

// Tag를 통해 Enum가져오기
EBlendSpaceMode UXZAnimInstance::GetEnumFromTag(FGameplayTag Tag)
{
	if (const EBlendSpaceMode* Enum = MatchingTagEnumMap.Find(Tag))
	{
		return MatchingTagEnumMap[Tag];
	}

	UE_LOG(LogTemp, Warning, TEXT("UXZAnimInstance::GetEnumFromTag - Do Not Have Matching type!"));
	return EBlendSpaceMode();
}

// 상태변경
void UXZAnimInstance::PlayMontageWithTag(FGameplayTag Tag)
{
	EBlendSpaceMode BlendSpaceMode = GetEnumFromTag(Tag);
	SetCurrentState(BlendSpaceMode);
}