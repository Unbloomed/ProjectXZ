#include "XZHpBarWidget.h"
#include "Components/ProgressBar.h"

UXZHpBarWidget::UXZHpBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UXZHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UXZHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp);
	}
}
