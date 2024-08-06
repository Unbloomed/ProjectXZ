// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "VM_XZStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UVM_XZStatComponent : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UVM_XZStatComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return CurrentHp; }
	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHp) { CurrentHp = NewHp; }
	UFUNCTION(BlueprintPure, FieldNotify)
	const float GetHealthPercent() const { return (CurrentHp / MaxHp); }

private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess = true, ExposeOnSpawn = true))
	float CurrentHp = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, ExposeOnSpawn = true))
	float MaxHp = 100.f;
};
