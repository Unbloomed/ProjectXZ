// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "XZCheatManager.generated.h"


#ifndef USING_CHEAT_MANAGER
#define USING_CHEAT_MANAGER (1 && !UE_BUILD_SHIPPING)
#endif // #ifndef USING_CHEAT_MANAGER

DECLARE_LOG_CATEGORY_EXTERN(LogXZCheat, Log, All);

class UXZStatComponent;
/**
 * 
 */
UCLASS(config = Game, Within = PlayerController, MinimalAPI)
class UXZCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	UXZCheatManager();
	
	virtual void InitCheatManager() override;

	// Helper function to write text to the console and to the log.
	static void CheatOutputText(const FString& TextToOutput);

	// Runs a cheat on the server for the owning player.
	UFUNCTION(exec)
	void Cheat(const FString& Msg);

	// Runs a cheat on the server for the all players.
	UFUNCTION(exec)
	void CheatAll(const FString& Msg);

	// Applies the specified damage amount to the owning player.
	UFUNCTION(Exec, BlueprintAuthorityOnly)
	virtual void DamageSelf(float DamageAmount);

	// Applies the specified damage amount to the actor that the player is looking at.
	virtual void DamageTarget(float DamageAmount) override;

	// Applies the specified amount of healing to the owning player.
	UFUNCTION(Exec, BlueprintAuthorityOnly)
	virtual void HealSelf(float HealAmount);

	// Applies the specified amount of healing to the actor that the player is looking at.
	UFUNCTION(Exec, BlueprintAuthorityOnly)
	virtual void HealTarget(float HealAmount);

	// Prevents the owning player from dropping below 1 health.
	UFUNCTION(Exec, BlueprintAuthorityOnly)
	virtual void UnlimitedHealth(int32 Enabled = -1);

	UFUNCTION(Exec, BlueprintAuthorityOnly)
	void CheatTest();


private:
	UXZStatComponent* GetStatComponent(const class AXZCharacter* Character) const;
	UXZStatComponent* GetStatComponent(class APlayerController* PC) const;
};
