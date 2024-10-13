// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XZCusomizingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API AXZCusomizingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AXZCusomizingPlayerController();
protected:
	virtual void BeginPlay() override;
};
