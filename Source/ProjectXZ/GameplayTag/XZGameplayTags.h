#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h" // GameplayTag Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½

/** native GamplayTagsï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Singleton
 *  ï¿½Úµï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½Í¿ï¿½ TDGameplayTags ï¿½ï¿½ï¿?
 */
struct FXZTags
{
public:
	static const FXZTags& GetXZTags() { return GameplayTags; }
	static void InitializeNativeGameplayTags(); // GameplayTags ï¿½ï¿½ï¿?

	// State
	FGameplayTag State_Unequipped;
	FGameplayTag State_Equipped;

	// Weapon
	FGameplayTag Fist;
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

	FGameplayTag InputTag_PickupItem;

	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_StopJumping;
	FGameplayTag InputTag_Crouch;
	FGameplayTag InputTag_Weapon_Reload;
	FGameplayTag InputTag_Weapon_Fire; 
	FGameplayTag InputTag_Weapon_Aim; 
	FGameplayTag InputTag_Weapon_StopAiming;

	//********************************************************
	// CharacterState
	FGameplayTag StateTag_Alive_Posture_Idle;
	FGameplayTag StateTag_Alive_Posture_Crouch;
	FGameplayTag StateTag_Alive_Posture_Jump;
	FGameplayTag StateTag_Alive_Equip_Idle;
	FGameplayTag StateTag_Alive_Equip_Aim;
	FGameplayTag StateTag_Alive_Equip_Shoulder;
	FGameplayTag StateTag_Alive_Equip_Fire;
	FGameplayTag StateTag_Respawn;
	FGameplayTag StateTag_Dead;

	//********************************************************
	// Game Team
	FGameplayTag GameTeamTag_None;
	FGameplayTag GameTeamTag_Red;
	FGameplayTag GameTeamTag_Blue;


	// Input ï¿½ï¿½ï¿½ï¿½: Pressed, Held, Released
	//FGameplayTag BlockTag_InputPressed;
	//FGameplayTag BlockTag_InputHeld;
	//FGameplayTag BlockTag_InputReleased;
	//********************************************************

private:
	static FXZTags GameplayTags;
};