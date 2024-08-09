#include "Widget/XZTimerWidget.h"
#include "Manager/XZTimerManager.h"
#include "Components/TextBlock.h"

UXZTimerWidget::UXZTimerWidget(const FObjectInitializer& ObjectInitializer)
{
}

void UXZTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
   
    bIsCountDown = true;
}

void UXZTimerWidget::StartTimer(float CountdownTime, bool bCountdown)
{
    CurrentTime = CountdownTime;
    bIsCountDown = bCountdown;
    
    UpdateTimerText();

    SetVisibility(ESlateVisibility::Visible);

    if (GetWorld())
    {
        if (UXZTimerManager* TimerManager = GetWorld()->GetGameInstance()->GetSubsystem<UXZTimerManager>())
        {
            FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UXZTimerWidget::UpdateTimer);
            TimerManager->SetTimer(CountdownTimerHandle, 1.0f, true, TimerDelegate);
        }
    }
}

void UXZTimerWidget::StopTimer()
{
    SetVisibility(ESlateVisibility::Hidden);

    if (GetWorld())
    {
        if( UXZTimerManager* TimerManager = GetWorld()->GetGameInstance()->GetSubsystem<UXZTimerManager>())
        {
            TimerManager->ClearTimer(CountdownTimerHandle);
        }
    }
}

void UXZTimerWidget::UpdateTimer()
{
    if (bIsCountDown)
    {
        CurrentTime -= 1.0f;
        if (CurrentTime <= 0.0f)
        {
            StopTimer();
            CurrentTime = 0.0f;
        }
    }
    else
    {
        CurrentTime += 1.0f;
    }
    
    UpdateTimerText();
}

void UXZTimerWidget::UpdateTimerText()
{
    if (TimerText)
    {
        TimerText->SetText(FText::AsNumber(FMath::CeilToInt(CurrentTime)));
    }
}
