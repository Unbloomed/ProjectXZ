#include "HUD/XZCustomizationHUD.h"
#include "Widget/Layers/XZModuleCustomizingLayer.h"
#include "Character/XZCharacter.h"

AXZCustomizationHUD::AXZCustomizationHUD()
{

}

void AXZCustomizationHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AXZCustomizationHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create CustomizingLayer
	if ( IsValid(CustomizingLayerClass) )
	{
		CustomizingLayer = CreateWidget<UXZModuleCustomizingLayer>(PlayerOwner, CustomizingLayerClass, TEXT("CustomizingLayer"));
		if ( IsValid(CustomizingLayer) )
		{
			CustomizingLayer->AddToViewport();

			AXZCharacter* Character = Cast<AXZCharacter>(GetOwningPawn());
			if ( nullptr == Character )
			{
				return;
			}
		}
	}
}
