#include "XZHpBarWidget.h"
#include "Components/ProgressBar.h"

UXZHpBarWidget::UXZHpBarWidget(const FObjectInitializer& ObjectInitializer)
{
}

void UXZHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	//ensure(HpProgressBar);
}

void UXZHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp);
	}
}
