// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/XZUserWidget.h"
#include "XZTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZTimerWidget : public UXZUserWidget
{
	GENERATED_BODY()
public:
		UXZTimerWidget(const FObjectInitializer& ObjectInitializer);
		
		// void UpdateTimerWidget();
		void StartTimer(float CountdownTime, bool bCountdown = true);
		void StopTimer();

protected:
	virtual void NativeConstruct() override;
	void UpdateTimer();
	void UpdateTimerText();

public:
	uint8 bIsCountDown : 1;

private:
	UPROPERTY( meta = (BindWidget))
	TObjectPtr<class UTextBlock> TimerText;
	FTimerHandle CountdownTimerHandle;

	float CurrentTime = 0.f;
};
