#include "XZHUD.h"
#include "Character/XZCharacter.h"
#include "Widget/XZHpBarWidget.h"
#include "Widget/XZTimerWidget.h"
#include "Widget/Windows/XZInventoryWindow.h"
#include "Widget/Layers/XZInGameLayer.h"
#include "Manager/XZUIManager.h"

AXZHUD::AXZHUD() 
{

}

void AXZHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerOwner == nullptr)
	{
		return;
	}

	if ( IsValid(InGameLayerClass) )
	{
		InGameLayer = CreateWidget<UXZInGameLayer>(PlayerOwner, InGameLayerClass, TEXT("InGameLayer"));
		if ( IsValid(InGameLayer) )
		{
			InGameLayer->AddToViewport();
		}
	}
	
	if ( IsValid(InventoryWindowClass) )
	{
		InventoryWindow = CreateWidget<UXZInventoryWindow>(PlayerOwner, InventoryWindowClass, TEXT("CustomizingLayer"));
		if ( IsValid(InventoryWindow) )
		{
			InventoryWindow->AddToViewport();
			InventoryWindow->CloseWindow();
		}
	}


	InGameLayer->OnInventoryButtonClickedeEvent.AddDynamic(this, &AXZHUD::OpenInventoryWindow);

	////////////////////////////////// Binding Delegate 
	// if (AXZCharacter* Character = Cast<AXZCharacter>(PlayerOwner->GetPawn()))
	// {
	// 	Character->SetUpWidget(this);
	// }
	////////////////////////////////////////////////////////////////////////////
}

void AXZHUD::OpenInventoryWindow()
{
	if ( IsValid(InventoryWindow) )
	{
		InventoryWindow->OpenWindow();
	}
}
