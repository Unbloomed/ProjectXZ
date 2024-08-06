#include "XZGameplayTags.h"
#include "GameplayTagsManager.h"

FXZTags FXZTags::GameplayTags; // static GamplayTags instance

void FXZTags::InitializeNativeGameplayTags()
{
	// Weapon
	GameplayTags.Weapon_Projectile_Rifle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Projectile.Rifle")), FString("소총"));
	GameplayTags.Weapon_Projectile_Pistol = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Projectile.Pistol")), FString("권총"));
	GameplayTags.Weapon_Projectile_SMG = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Projectile.SMG")), FString("서브머신건"));
	GameplayTags.Weapon_Hitscan_SnipperRifle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Hitscan.SnipperRifle")), FString("저격총"));
	GameplayTags.Weapon_Hitscan_Shotgun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Hitscan.Shotgun")), FString("샷건"));
	GameplayTags.Weapon_Melee_Dagger = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Melee.Dagger")), FString("단검"));
	GameplayTags.Weapon_Melee_Axe = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Melee.Axe")), FString("단검"));

	// State
	GameplayTags.State_Unequipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Unequipped")), FString("장착 해제"));
	GameplayTags.State_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Equipped")), FString("장착"));

	//************************************************************************************************
	// Character State
	GameplayTags.StateTag_Alive_Posture_Idle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Alive.Posture.Idle")), FString("기본 상태"));
	GameplayTags.StateTag_Alive_Posture_Crouch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Alive.Posture.Crouch")), FString("앉기 상태"));
	GameplayTags.StateTag_Alive_Posture_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Alive.Posture.Jump")), FString("점프 상태"));
	GameplayTags.StateTag_Alive_Equip_Idle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Alive.Equip.Idle")), FString("장착 기본 상태"));
	GameplayTags.StateTag_Alive_Equip_Aim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Alive.Equip.Aim")), FString("장착 조준 상태"));
	GameplayTags.StateTag_Alive_Equip_Shoulder = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Alive.Equip.Shoulder")), FString("장착 견착 상태"));
	GameplayTags.StateTag_Alive_Equip_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Alive.Equip.Fire")), FString("장착 발사 상태"));
	GameplayTags.StateTag_Respawn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Respawn")), FString("리스폰 상태"));
	GameplayTags.StateTag_Dead = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("State.Dead")), FString("죽은 자세"));

	//************************************************************************************************
	// Enhanced Input
	GameplayTags.InputTag_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Move"), FString("이동 버튼 Input Tag"));
	GameplayTags.InputTag_Look_Mouse = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Look.Mouse"), FString("마우스 Input Tag"));

	GameplayTags.InputTag_PickupItem = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.PickupItem"), FString("아이템 줍기 Input Tag"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("1 Input Tag"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("2 Input Tag"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("3 Input Tag"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("4 Input Tag"));

	GameplayTags.InputTag_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Jump"), FString("점프 Input Tag"));
	GameplayTags.InputTag_StopJumping = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.StopJumping"), FString("점프X Input Tag"));
	GameplayTags.InputTag_Crouch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Crouch"), FString("쪼그려 앉기 버튼 Input Tag"));
	GameplayTags.InputTag_Weapon_Reload = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Weapon_Reload"), FString("재장전 버튼 Input Tag"));
	GameplayTags.InputTag_Weapon_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Weapon_Fire"), FString("발사 버튼 Input Tag"));
	GameplayTags.InputTag_Weapon_Aim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Weapon_Aim"), FString("조준 버튼 Input Tag"));
	GameplayTags.InputTag_Weapon_StopAiming = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Weapon_StopAiming"), FString("조준X Input Tag"));


	// Input 상태: Pressed, Held, Released
	//GameplayTags.BlockTag_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputPressed"), FString("Block: Input Pressed 상태"));
	//GameplayTags.BlockTag_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputHeld"), FString("Block: Input Held 상태"));
	//GameplayTags.BlockTag_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputReleased"), FString("Block: Input Released 상태"));
	//************************************************************************************************
}
