#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h" // GameplayTag 타占쏙옙 占쏙옙占쏙옙

/** native GamplayTags占쏙옙 占쏙옙占쏙옙占쏙옙 Singleton
 *  占쌘듸옙占?占쏙옙占쏙옙占싶울옙 TDGameplayTags 占쏙옙占?
 */
struct FXZTags
{
public:
	static const FXZTags& GetXZTags() { return GameplayTags; }
	static void InitializeNativeGameplayTags(); // GameplayTags 占쏙옙占?

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


	// Input 占쏙옙占쏙옙: Pressed, Held, Released
	//FGameplayTag BlockTag_InputPressed;
	//FGameplayTag BlockTag_InputHeld;
	//FGameplayTag BlockTag_InputReleased;


	// Parts
	FGameplayTag Part_Muzzle_None;
	FGameplayTag Part_Muzzle_Suppressor;
	FGameplayTag Part_Muzzle_FlashHider;
	FGameplayTag Part_Muzzle_Compensator;
	
	FGameplayTag Part_Magazine_None;
	FGameplayTag Part_Magazine_ExtendedMagazine;
	FGameplayTag Part_Magazine_QuickdrawMagazine;
	
	FGameplayTag Part_Stock_None;
	FGameplayTag Part_Stock_Stock;
	FGameplayTag Part_Stock_CheekPad;

	FGameplayTag Part_Scope_None;
	FGameplayTag Part_Scope_RedDotSight;
	FGameplayTag Part_Scope_2xScope;
	FGameplayTag Part_Scope_4xScope;
	FGameplayTag Part_Scope_8xScope;
	FGameplayTag Part_Scope_15xScope;

	// Item
	FGameplayTag Consumable_Medical_FirstAidKit;
	FGameplayTag Consumable_Medical_MedKit;
	FGameplayTag Consumable_Booster_Painkiller;
	FGameplayTag Consumable_Booster_AdrenalineSyringe;
	FGameplayTag Consumable_Booster_EnergyDrink;

	// Equipment
	FGameplayTag Equipment_Supply_Backpack;
	FGameplayTag Equipment_Armor_Vest;
	FGameplayTag Equipment_Armor_Helmet;
	 
	 
	//********************************************************
	 // Widgets
	FGameplayTag Widget_Layer_FullUI;
	FGameplayTag Widget_Layer_PopUpType;
	FGameplayTag Widget_Layer_SubPopUpType;
	FGameplayTag Widget_Layer_TutorialType;
	FGameplayTag Widget_Layer_NoticeType;
	 
	//********************************************************

private:
	static FXZTags GameplayTags;
};