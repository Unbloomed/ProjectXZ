#include "Handler/XZCombatHandler.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Character/XZCharacter.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/XZDA_Weapon.h"
#include "Weapon/Attachment/XZAttachment.h"

bool UXZCombatHandler::IsValidWeapon(const FGameplayTag& InTag)
{
	if ( UXZDA_Weapon** FoundData = DA_Weapons.Find(InTag) )
	{
		if ( *FoundData )
		{
			return true;
		}

		UE_LOG(LogTemp, Warning, TEXT("FoundData(=XZWeaponData) is nullptr"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Weapon is not found. Check UXZWeaponComponent::EquipWeapon"));
	return false;
}

void UXZCombatHandler::AddNewWeapon(const FGameplayTag& InTag, UXZDA_Weapon* DA_Weapon, ACharacter* InOwner)
{
	if (IsValidWeapon(InTag)) return;

	OwnerCharacter = InOwner;

	DA_Weapons.Add({ InTag, DA_Weapon });

	AXZAttachment* Weapon = OwnerCharacter->GetWorld()->SpawnActor<AXZAttachment>(DA_Weapons[InTag]->AttachmentClass);
	WeaponActors.Add({ InTag, Weapon });

	if ( DA_Weapons[InTag]->EquipmentData.HolsterSocketName.IsValid() )
	{
		WeaponActors[InTag]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), DA_Weapons[InTag]->EquipmentData.HolsterSocketName);
	}

	// Create Crosshair
	if ( IsValid(DA_Weapons[InTag]->AimData.AimCurve) && IsValid(Timeline) )
	{
		FOnTimelineFloat TimelineFloat;
		TimelineFloat.BindUFunction(this, "OnAiming");

		Timeline->AddInterpFloat(DA_Weapons[InTag]->AimData.AimCurve, TimelineFloat);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(DA_Weapons[InTag]->AimData.AimingSpeed);
	}

	if ( DA_Weapons[InTag]->AimData.CrosshairWidgetClass )
	{
		APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());

		Crosshair = CreateWidget<UUserWidget>(PC, DA_Weapons[InTag]->AimData.CrosshairWidgetClass);
		if ( Crosshair )
		{
			Crosshair->AddToViewport();
			Crosshair->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create Crosshair widget."));
		}
	}
}

void UXZCombatHandler::Equip(const FGameplayTag& InTag)
{
	if ( false == IsValid(OwnerCharacter) ) return;

	if ( bEquipped )
	{
		Unequip(InTag);
		return;
	}

	if ( IsValid(DA_Weapons[InTag]->EquipmentData.EquipMontage) )
	{
		// Play Equip Montange Animation
		OwnerCharacter->PlayAnimMontage(DA_Weapons[InTag]->EquipmentData.EquipMontage);

		// Attach WeaponMesh to RightHand
		FTimerHandle EquipTimerHandle;
		FTimerDelegate EquipTimerDelegate = FTimerDelegate::CreateLambda([this, InTag]
			{ this->ChangeSocket_Equip(InTag); }
		);
		OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(EquipTimerHandle, EquipTimerDelegate, DA_Weapons[InTag]->EquipmentData.Equip_FrameTime, false);

		EquippedTag = InTag;
		bEquipped = true;
	}
}

void UXZCombatHandler::Unequip(const FGameplayTag& InTag)
{
	if ( IsValid(DA_Weapons[InTag]->EquipmentData.UnequipMontage) )
	{
		// Play Equip Montange Animation
		OwnerCharacter->PlayAnimMontage(DA_Weapons[InTag]->EquipmentData.UnequipMontage);

		// Attach WeaponMesh (from Holster Socket) to Hand Socket
		FTimerHandle UnequipTimerHandle;
		FTimerDelegate UnequipTimerDelegate = FTimerDelegate::CreateLambda([ this, InTag ]
			{ this->ChangeSocket_Unequip(InTag); }
		);
		OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(UnequipTimerHandle, UnequipTimerDelegate, DA_Weapons[InTag]->EquipmentData.Unequip_FrameTime, false);

		bEquipped = false;
	}
}

void UXZCombatHandler::ChangeSocket_Equip(const FGameplayTag& InTag)
{
	if ( DA_Weapons[InTag]->EquipmentData.WeaponSocketName.IsValid() )
	{
		WeaponActors[InTag]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), DA_Weapons[InTag]->EquipmentData.WeaponSocketName);
	}
}

void UXZCombatHandler::ChangeSocket_Unequip(const FGameplayTag& InTag)
{

}

TObjectPtr<USpringArmComponent> UXZCombatHandler::GetXZCharacterSpringArm()
{
	if ( CameraSpringArm ) return CameraSpringArm;

	CameraSpringArm = Cast<AXZCharacter>(OwnerCharacter)->GetSpringArm();
	return CameraSpringArm;
}

TObjectPtr<UCameraComponent> UXZCombatHandler::GetFollowCamera()
{
	if ( FollowCamera ) return FollowCamera;

	FollowCamera = Cast<AXZCharacter>(OwnerCharacter)->GetFollowCamera();
	return FollowCamera;
}

void UXZCombatHandler::ShowCrosshair(bool bShowCrosshair)
{
	if ( false == IsValid(Crosshair) ) return;

	if ( bShowCrosshair )
	{
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Crosshair->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UXZCombatHandler::StartAiming()
{
	if ( IsValid(DA_Weapons[EquippedTag]->AimData.AimCurve) )
	{
		Timeline->PlayFromStart();

		GetXZCharacterSpringArm()->TargetArmLength = DA_Weapons[EquippedTag]->AimData.WeaponZoomData.TargetArmLength;
		GetXZCharacterSpringArm()->SocketOffset = DA_Weapons[EquippedTag]->AimData.WeaponZoomData.SocketOffset;
		GetXZCharacterSpringArm()->bEnableCameraLag = DA_Weapons[EquippedTag]->AimData.WeaponZoomData.bEnableCameraLag;
	}
}

void UXZCombatHandler::EndAiming()
{
	if ( IsValid(DA_Weapons[EquippedTag]->AimData.AimCurve) )
	{
		Timeline->ReverseFromEnd();

		GetXZCharacterSpringArm()->TargetArmLength = DA_Weapons[EquippedTag]->AimData.BaseZoomData.TargetArmLength;
		GetXZCharacterSpringArm()->SocketOffset = DA_Weapons[EquippedTag]->AimData.BaseZoomData.SocketOffset;
		GetXZCharacterSpringArm()->bEnableCameraLag = DA_Weapons[EquippedTag]->AimData.BaseZoomData.bEnableCameraLag;
	}
}

void UXZCombatHandler::OnAiming(float Output)
{
	GetFollowCamera()->FieldOfView = FMath::Lerp(DA_Weapons[EquippedTag]->AimData.WeaponZoomData.FieldOfView, DA_Weapons[EquippedTag]->AimData.BaseZoomData.FieldOfView, Output);
}
