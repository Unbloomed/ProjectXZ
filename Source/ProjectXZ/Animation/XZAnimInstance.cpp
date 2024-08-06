// Fill out your copyright notice in the Description page of Project Settings.


#include "../Animation/XZAnimInstance.h"
#include "../GameplayTag/XZGameplayTags.h"

// Tag�� ���� Enum��������
EBlendSpaceMode UXZAnimInstance::GetEnumFromTag(FGameplayTag Tag)
{
	if (const EBlendSpaceMode* Enum = MatchingTagEnumMap.Find(Tag))
	{
		return MatchingTagEnumMap[Tag];
	}

	UE_LOG(LogTemp, Warning, TEXT("UXZAnimInstance::GetEnumFromTag - Do Not Have Matching type!"));
	return EBlendSpaceMode();
}

// ���º���
void UXZAnimInstance::PlayMontageWithTag(const FGameplayTag& Tag)
{
	EBlendSpaceMode BlendSpaceMode = GetEnumFromTag(Tag);
	SetCurrentState(BlendSpaceMode);
	UE_LOG(LogTemp, Log, TEXT("%s"), BlendSpaceMode);
}