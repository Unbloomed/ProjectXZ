// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XZDamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXZDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTXZ_API IXZDamageInterface
{
	GENERATED_BODY()
public:
	virtual void TakeDamage(float DamageAmount) = 0;
};
