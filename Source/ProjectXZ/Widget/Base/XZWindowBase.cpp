
#include "XZWindowBase.h"
#include "GameplayTag/XZGameplayTags.h"
#include "Character/XZCharacter.h"

UXZWindowBase::UXZWindowBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UXZWindowBase::OpenWindow()
{
	this->SetVisibility(ESlateVisibility::Visible);

	UE_LOG(LogTemp, Log, TEXT("[Test] OpenWindow 1"));

	if ( WindowType == FXZTags::GetXZTags().Widget_UIType_FullUI ) 
	{
		if ( AXZCharacter* Character = Cast< AXZCharacter>(GetOwningPlayerPawn()) ) 
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] OpenWindow 1"));
			Character->StartUIMode();
		}
	}
}

void UXZWindowBase::CloseWindow()
{
	this->SetVisibility(ESlateVisibility::Hidden);

	UE_LOG(LogTemp, Log, TEXT("[Test] CloseWindow 1"));

	if ( WindowType == FXZTags::GetXZTags().Widget_UIType_FullUI )
	{
		if ( AXZCharacter* Character = Cast< AXZCharacter>(GetOwningPlayerPawn()) )
		{
			Character->EndUIMode();
		}
	}
	
}
