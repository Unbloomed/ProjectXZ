// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Character/XZCharacter.h"
#include "XZSpawnManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZSpawnManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UXZSpawnManager();
	void RequestSpawnCharacter(class APawn* Pawn, const FGenericTeamId& TeamID = 0);

protected:
	virtual void PostInitialize() override;

private:
	TMap<FGenericTeamId, TObjectPtr<class AXZSpawnPoint>> PlayerSpawnPoints;
};
