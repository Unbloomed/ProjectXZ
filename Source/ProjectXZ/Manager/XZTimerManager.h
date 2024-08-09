// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "XZTimerManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZTimerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UXZTimerManager();
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // 추후 FTimerHandle& TimerHandle는 ObjectPool로 관리 예정
    void SetTimer(FTimerHandle& TimerHandle, float Time, bool bLooping, FTimerDelegate TimerCallback);
    void ClearTimer(FTimerHandle& TimerHandle);
};
