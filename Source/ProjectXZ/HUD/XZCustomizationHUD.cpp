#include "HUD/XZCustomizationHUD.h"
#include "Widget/XZModuleCustomizingLayer.h"
#include "Widget/XZModuleSelectSlot.h"
#include "Character/XZCharacter.h"
#include "Component/XZModularComponent.h"

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

			UXZModularComponent* ModularComponent = Character->GetModularComponent();

			if ( nullptr == ModularComponent )
			{
				return;
			}
		}
	}
}
