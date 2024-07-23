#include "XZGameplayTags.h"
#include "GameplayTagsManager.h"

FXZTags FXZTags::GameplayTags; // static GamplayTags instance

void FXZTags::InitializeNativeGameplayTags()
{
	// Weapon
	GameplayTags.Weapon_Projectile_Rifle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Projectile.Rifle")), FString("소총"));
	GameplayTags.Weapon_Projectile_Pistol = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Projectile.Pistol")), FString("권총"));
	GameplayTags.Weapon_Projectile_Rifle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Projectile.SMG")), FString("서브머신건"));
	GameplayTags.Weapon_Hitscan_SnipperRifle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Hitscan.SnipperRifle")), FString("저격총"));
	GameplayTags.Weapon_Hitscan_Shotgun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Hitscan.Shotgun")), FString("샷건"));
	GameplayTags.Weapon_Melee_Dagger = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Melee.Dagger")), FString("단검"));
	GameplayTags.Weapon_Melee_Axe = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TEXT("Weapon.Melee.Axe")), FString("단검"));

	//************************************************************************************************
	// Enhanced Input
	GameplayTags.InputTag_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Move"), FString("이동 버튼 Input Tag"));
	GameplayTags.InputTag_Look_Mouse = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Look.Mouse"), FString("마우스 Input Tag"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("1 Input Tag"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("2 Input Tag"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("3 Input Tag"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("4 Input Tag"));

	GameplayTags.InputTag_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Jump"), FString("점프 Input Tag"));
	GameplayTags.InputTag_Crouch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Crouch"), FString("쪼그려 앉기 버튼 Input Tag"));
	GameplayTags.InputTag_Weapon_Reload = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Weapon_Reload"), FString("재장전 버튼 Input Tag"));
	GameplayTags.InputTag_Weapon_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Weapon_Fire"), FString("발사 버튼 Input Tag"));

	// Input 상태: Pressed, Held, Released
	//GameplayTags.BlockTag_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputPressed"), FString("Block: Input Pressed 상태"));
	//GameplayTags.BlockTag_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputHeld"), FString("Block: Input Held 상태"));
	//GameplayTags.BlockTag_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputReleased"), FString("Block: Input Released 상태"));
	//************************************************************************************************
}
