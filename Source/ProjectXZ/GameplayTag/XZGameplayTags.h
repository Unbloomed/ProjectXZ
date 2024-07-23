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

	// State
	FGameplayTag State_UnEquipped;
	FGameplayTag State_Equipped;


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
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;

	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Crouch;
	FGameplayTag InputTag_Weapon_Reload;
	FGameplayTag InputTag_Weapon_Fire;

	// Input 상태: Pressed, Held, Released
	//FGameplayTag BlockTag_InputPressed;
	//FGameplayTag BlockTag_InputHeld;
	//FGameplayTag BlockTag_InputReleased;
	//********************************************************

private:
	static FXZTags GameplayTags;
};