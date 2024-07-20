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
	GameplayTags.InputTag_A = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.A"), FString("A버튼 Input Tag"));
	GameplayTags.InputTag_W = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.W"), FString("W버튼 Input Tag"));
	GameplayTags.InputTag_S = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.S"), FString("S버튼 Input Tag"));
	GameplayTags.InputTag_D = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.D"), FString("D버튼 Input Tag"));
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("왼쪽 마우스 버튼 Input Tag"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("오른쪽 마우스 버튼 Input Tag"));
	GameplayTags.InputTag_Spacebar = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Spacebar"), FString("스페이스바 버튼 Input Tag"));
	GameplayTags.InputTag_Ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Ctrl"), FString("Ctrl 버튼 Input Tag"));

	// Input 상태: Pressed, Held, Released
	GameplayTags.BlockTag_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputPressed"), FString("Block: Input Pressed 상태"));
	GameplayTags.BlockTag_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputHeld"), FString("Block: Input Held 상태"));
	GameplayTags.BlockTag_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputReleased"), FString("Block: Input Released 상태"));
	//************************************************************************************************
}
