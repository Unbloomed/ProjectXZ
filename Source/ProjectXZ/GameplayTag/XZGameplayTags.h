#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h" // GameplayTag Ÿ�� ����

/** native GamplayTags�� ������ Singleton
 *  �ڵ�� �����Ϳ� TDGameplayTags ���
 */
struct FXZTags
{
public:
	static const FXZTags& GetXZTags() { return GameplayTags; }
	static void InitializeNativeGameplayTags(); // GameplayTags ���

	void RegisterTag(const FName& TagName);

	// State
	FGameplayTag State_UnEquipped;
	FGameplayTag State_Equipped;


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
	FGameplayTag InputTag_Weapon_Aim; 

	// Input ����: Pressed, Held, Released
	//FGameplayTag BlockTag_InputPressed;
	//FGameplayTag BlockTag_InputHeld;
	//FGameplayTag BlockTag_InputReleased;
	//********************************************************

private:
	static FXZTags GameplayTags;
};