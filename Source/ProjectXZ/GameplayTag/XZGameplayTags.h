#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h" // GameplayTag 타입 정보

/** native GamplayTags를 가지는 Singleton
 *  코드로 에디터에 TDGameplayTags 등록
 */
struct FXZTags
{
public:
	static const FXZTags& GetXZTags() { return GameplayTags; }
	static void InitializeNativeGameplayTags(); // GameplayTags 등록

	// Weapon
	FGameplayTag Weapon_Projectile_Rifle;
	FGameplayTag Weapon_Projectile_Pistol;
	FGameplayTag Weapon_Projectile_SMG;
	FGameplayTag Weapon_Hitscan_SnipperRifle;
	FGameplayTag Weapon_Hitscan_Shotgun;
	FGameplayTag Weapon_Melee_Dagger;
	FGameplayTag Weapon_Melee_Axe;

	//********************************************************
	// Enhanced Input
	FGameplayTag InputTag_A;
	FGameplayTag InputTag_W;
	FGameplayTag InputTag_S;
	FGameplayTag InputTag_D;
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Spacebar; // Jump
	FGameplayTag InputTag_Ctrl;		// Crouch

	// Input 상태: Pressed, Held, Released
	FGameplayTag BlockTag_InputPressed;
	FGameplayTag BlockTag_InputHeld;
	FGameplayTag BlockTag_InputReleased;
	//********************************************************

private:
	static FXZTags GameplayTags;
};