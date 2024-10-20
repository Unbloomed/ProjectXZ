#include "XZTopBarLayer.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Widget/Slots/XZCashSlot.h"

UXZTopBarLayer::UXZTopBarLayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UXZTopBarLayer::NativeConstruct()
{
	Super::NativeConstruct();

	if ( CloseButton )
	{
		CloseButton->OnClicked.AddDynamic(this, &UXZTopBarLayer::OnCloseButtonClicked);
	}

	if ( MailButton )
	{
		MailButton->OnClicked.AddDynamic(this, &UXZTopBarLayer::OnMailButtonClicked);
	}

	if ( HomeButton )
	{
		HomeButton->OnClicked.AddDynamic(this, &UXZTopBarLayer::OnHomeButtonClicked);
	}

	if ( MenuToggleButton )
	{
		MenuToggleButton->OnClicked.AddDynamic(this, &UXZTopBarLayer::OnMenuToggleButtonClicked);
	}

	OnInitialize();
}

void UXZTopBarLayer::NativeDestruct()
{
	Super::NativeDestruct();
}

// void UXZTopBarLayer::InitializeData(FXZTopBarLayerInfo NewTopBarLayerInfo)
// {
// 	if ( ContentsInformationText ) 
// 	{
// 		ContentsInformationText->SetText(FText::FromString(NewTopBarLayerInfo.ContentsInformationString));
// 	}
// 
// 	if ( false == NewTopBarLayerInfo.bVisibleCashSlot )
// 	{
// 		// if ( CashSlot ) 
// 		// {
// 		// 	CashSlot->SetVisibility(EVisibility::Hidden);
// 		// }
// 	}
// }

void UXZTopBarLayer::OnCloseButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UXZTopBarLayer::OnCloseButtonClicked"));
}

void UXZTopBarLayer::OnMailButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UXZTopBarLayer::OnMailButtonClicked"));
}

void UXZTopBarLayer::OnHomeButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UXZTopBarLayer::OnHomeButtonClicked"));
}

void UXZTopBarLayer::OnMenuToggleButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UXZTopBarLayer::OnMenuToggleButtonClicked"));
}

void UXZTopBarLayer::OnInitialize()
{
	UE_LOG(LogTemp, Log, TEXT("[UI OnInitialize] "));

	if(ContentsInformationText)
	{
		UE_LOG(LogTemp, Log, TEXT("[UI Test] %s"), *TopBarLayerInfo.ContentsInformationString);
		ContentsInformationText->SetText(FText::FromString(TopBarLayerInfo.ContentsInformationString));
	}

	if ( CashSlot ) 
	{
		CashSlot->SetVisibility(TopBarLayerInfo.CashSlotVisibility);
	}
}

void UXZTopBarLayer::OnUpdate()
{
}
