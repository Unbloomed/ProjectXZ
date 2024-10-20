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

	//********************************************************
	// Game Team
	GameplayTags.GameTeamTag_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameTeamTag.None"), FString("팀 None Game Tag"));
	GameplayTags.GameTeamTag_Red = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameTeamTag.Red"), FString("팀 Red Game Tag"));
	GameplayTags.GameTeamTag_Blue = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameTeamTag.Blue"), FString("팀 Blue Game Tag"));


	//************************************************************************************************
	// Parts :: Muzzle
	GameplayTags.Part_Muzzle_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Muzzle.None"), FString("파츠 Muzzle 없음 Tag"));
	GameplayTags.Part_Muzzle_Suppressor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Muzzle.Suppressor"), FString("파츠 소음기 Tag"));
	GameplayTags.Part_Muzzle_FlashHider = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Muzzle.FlashHider"), FString("파츠 소염기 Tag"));
	GameplayTags.Part_Muzzle_Compensator = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Muzzle.Compensator"), FString("파츠 보정기 Tag"));
		
	// Parts :: Magazine
	GameplayTags.Part_Magazine_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Magazine.None"), FString("파츠 탄창 없음 Tag"));
	GameplayTags.Part_Magazine_ExtendedMagazine = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Magazine.ExtendedMagazine"), FString("파츠 대용량 탄창 Tag"));
	GameplayTags.Part_Magazine_QuickdrawMagazine = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Magazine.QuickdrawMagazine"), FString("파츠 퀵드로우 탄창 Tag"));

	// Parts :: Stock
	GameplayTags.Part_Stock_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Stock.None"), FString("파츠 개머리판 없음 Tag"));
	GameplayTags.Part_Stock_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Stock.Buttstock"), FString("파츠 개머리판 개머리판 Tag"));
	GameplayTags.Part_Muzzle_Compensator = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Stock.CheekPad"), FString("파츠 개머리판 칙패드 Tag"));

	// Parts :: Scope
	GameplayTags.Part_Scope_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Scope.None"), FString("파츠 배율 없음 Tag"));
	GameplayTags.Part_Scope_RedDotSight = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Scope.RedDotSight"), FString("파츠 배율 레드도트 사이트 Tag"));
	GameplayTags.Part_Scope_2xScope = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Scope.2xScope"), FString("파츠 배율 2배율 스코프 Tag"));
	GameplayTags.Part_Scope_4xScope = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Scope.4xScope"), FString("파츠 배율 4배율 스코프 Tag"));
	GameplayTags.Part_Scope_8xScope = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Scope.8xScope"), FString("파츠 배율 8배율 스코프 Tag"));
	GameplayTags.Part_Scope_15xScope = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Part.Scope.15xScope"), FString("파츠 배율 15배율 스코프 Tag"));

	// Item
	GameplayTags.Consumable_Medical_FirstAidKit = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Consumable.Medical.FirstAidKit"), FString("아이템 구급상자 Tag"));
	GameplayTags.Consumable_Medical_MedKit = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Consumable.Medical.MedKit"), FString("아이템 의료용 키트 Tag"));

	GameplayTags.Consumable_Booster_Painkiller = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Consumable.Booster.Painkiller"), FString("아이템 진통제 Tag"));
	GameplayTags.Consumable_Booster_AdrenalineSyringe = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Consumable.Booster.AdrenalineSyringe"), FString("아이템 아드레날린 주사 Tag"));
	GameplayTags.Consumable_Booster_EnergyDrink = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Consumable.Booster.EnergyDrink"), FString("아이템 에너지 드링크 Tag"));

	// Equipment
	GameplayTags.Equipment_Supply_Backpack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Supply.Backpack"), FString("장착 아이템 가방 Tag"));
	GameplayTags.Equipment_Armor_Vest = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Armor.Vest"), FString("장착 아이템 조끼 Tag"));
	GameplayTags.Equipment_Armor_Helmet = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Armor.Helmet"), FString("장착 아이템 헬멧 Tag"));

	//********************************************************
	// Widgets
	GameplayTags.Widget_UIType_FullUI = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.UIType.FullUI"), FString("UI 전체 화면"));
	GameplayTags.Widget_UIType_PopUpType = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.UIType.PopUpType"), FString("팝업 UI"));
	GameplayTags.Widget_UIType_SubPopUpType = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.UIType.SubPopUpType"), FString("SubPopUp UI"));
	GameplayTags.Widget_UIType_TutorialType = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.UIType.TutorialType"), FString("튜토리얼 UI"));
	GameplayTags.Widget_UIType_NoticeType = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.UIType.NoticeType"), FString("Notice UI"));

	// Input 상태: Pressed, Held, Released
	//GameplayTags.BlockTag_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputPressed"), FString("Block: Input Pressed 상태"));
	//GameplayTags.BlockTag_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputHeld"), FString("Block: Input Held 상태"));
	//GameplayTags.BlockTag_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.InputReleased"), FString("Block: Input Released 상태"));
	//************************************************************************************************
}
