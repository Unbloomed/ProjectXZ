#include "XZHUD.h"
#include "Widget/XZHpBarWidget.h"

AXZHUD::AXZHUD() 
{
	static ConstructorHelpers::FClassFinder<UXZHpBarWidget> HpBarWidgetClassRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP/Widget/BP_TestHPBar.BP_TestHPBar_C'"));
	if (HpBarWidgetClassRef.Class)
	{
		HpBarWidgetClass = HpBarWidgetClassRef.Class;
	}
}

void AXZHUD::DrawHUD()
{
	Super::DrawHUD();

	APlayerController* PC = GetOwningPlayerController();
	if (IsValid(PC) && CharacterOverlayWidgetClass)
	{
		CharacterOverlayWidget = CreateWidget<UUserWidget>(PC, CharacterOverlayWidgetClass);
	}
}

void AXZHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(CharacterOverlayWidget))
	{
		CharacterOverlayWidget->AddToViewport();
		CharacterOverlayWidget->SetVisibility(ESlateVisibility::Visible);
	}

	// Create HpBarWidget
	if (HpBarWidgetClass)
	{
		HpBarWidget = CreateWidget<UXZHpBarWidget>(PlayerOwner, HpBarWidgetClass, TEXT("HpBarWidget"));
		if (HpBarWidget)
		{
			HpBarWidget->AddToViewport();
		}
	}
}

void AXZHUD::UpdateHPBarWidget(float MaxHP, float CurrentHP)
{
	const float NewPercent = FMath::Clamp((CurrentHP / MaxHP), 0.0f, 1.0f);
	HpBarWidget->UpdateHpBar(NewPercent);
}

