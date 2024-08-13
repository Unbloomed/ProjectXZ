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
	AXZAttachment** FoundData = Attachments.Find(InTag);
	if ( nullptr == *FoundData )
	{
		return false;
	}
	
	return true;
}

void UXZCombatHandler::AddNewWeapon(const FGameplayTag& InTag, ACharacter* InOwner)
{
	//if (IsValidWeapon(InTag))
	{
	//	return;
	}

	OwnerCharacter = InOwner;

	AXZAttachment* Weapon = OwnerCharacter->GetWorld()->SpawnActor<AXZAttachment>(Attachments[InTag]->DA_Weapon->AttachmentClass);
	Attachments.Add({ InTag, Weapon });

	if ( Attachments[InTag]->DA_Weapon->EquipmentData.HolsterSocketName.IsValid() )
	{
		Attachments[InTag]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Attachments[InTag]->DA_Weapon->EquipmentData.HolsterSocketName);
	}

	// Create Crosshair
	if ( IsValid(Attachments[InTag]->DA_Weapon->AimData.AimCurve) && IsValid(Timeline) )
	{
		FOnTimelineFloat TimelineFloat;
		TimelineFloat.BindUFunction(this, "OnAiming");

		Timeline->AddInterpFloat(Attachments[InTag]->DA_Weapon->AimData.AimCurve, TimelineFloat);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(Attachments[InTag]->DA_Weapon->AimData.AimingSpeed);
	}

	if ( Attachments[InTag]->DA_Weapon->AimData.CrosshairWidgetClass )
	{
		APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());

		Crosshair = CreateWidget<UUserWidget>(PC, Attachments[InTag]->DA_Weapon->AimData.CrosshairWidgetClass);
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

	if ( IsValid(Attachments[InTag]->DA_Weapon->EquipmentData.EquipMontage) )
	{
		// Play Equip Montange Animation
		OwnerCharacter->PlayAnimMontage(Attachments[InTag]->DA_Weapon->EquipmentData.EquipMontage);

		// Attach WeaponMesh to RightHand
		FTimerHandle EquipTimerHandle;
		FTimerDelegate EquipTimerDelegate = FTimerDelegate::CreateLambda([this, InTag]
			{ this->ChangeSocket_Equip(InTag); }
		);
		OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(EquipTimerHandle, EquipTimerDelegate, Attachments[InTag]->DA_Weapon->EquipmentData.Equip_FrameTime, false);

		EquippedTag = InTag;
		bEquipped = true;
	}
}

void UXZCombatHandler::Unequip(const FGameplayTag& InTag)
{
	if ( IsValid(Attachments[InTag]->DA_Weapon->EquipmentData.UnequipMontage) )
	{
		// Play Equip Montange Animation
		OwnerCharacter->PlayAnimMontage(Attachments[InTag]->DA_Weapon->EquipmentData.UnequipMontage);

		// Attach WeaponMesh (from Holster Socket) to Hand Socket
		FTimerHandle UnequipTimerHandle;
		FTimerDelegate UnequipTimerDelegate = FTimerDelegate::CreateLambda([ this, InTag ]
			{ this->ChangeSocket_Unequip(InTag); }
		);
		OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(UnequipTimerHandle, UnequipTimerDelegate, Attachments[InTag]->DA_Weapon->EquipmentData.Unequip_FrameTime, false);

		bEquipped = false;
	}
}

void UXZCombatHandler::ChangeSocket_Equip(const FGameplayTag& InTag)
{
	if ( Attachments[InTag]->DA_Weapon->EquipmentData.WeaponSocketName.IsValid() )
	{
		Attachments[InTag]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Attachments[InTag]->DA_Weapon->EquipmentData.WeaponSocketName);
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
	if ( IsValid(Attachments[EquippedTag]->DA_Weapon->AimData.AimCurve) )
	{
		Timeline->PlayFromStart();

		GetXZCharacterSpringArm()->TargetArmLength = Attachments[EquippedTag]->DA_Weapon->AimData.WeaponZoomData.TargetArmLength;
		GetXZCharacterSpringArm()->SocketOffset = Attachments[EquippedTag]->DA_Weapon->AimData.WeaponZoomData.SocketOffset;
		GetXZCharacterSpringArm()->bEnableCameraLag = Attachments[EquippedTag]->DA_Weapon->AimData.WeaponZoomData.bEnableCameraLag;
	}
}

void UXZCombatHandler::EndAiming()
{
	if ( IsValid(Attachments[EquippedTag]->DA_Weapon->AimData.AimCurve) )
	{
		Timeline->ReverseFromEnd();

		GetXZCharacterSpringArm()->TargetArmLength = Attachments[EquippedTag]->DA_Weapon->AimData.BaseZoomData.TargetArmLength;
		GetXZCharacterSpringArm()->SocketOffset = Attachments[EquippedTag]->DA_Weapon->AimData.BaseZoomData.SocketOffset;
		GetXZCharacterSpringArm()->bEnableCameraLag = Attachments[EquippedTag]->DA_Weapon->AimData.BaseZoomData.bEnableCameraLag;
	}
}

void UXZCombatHandler::Fire(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation)
{
	Server_Fire(InTag, HitLocation);
}


void UXZCombatHandler::Server_Fire_Implementation(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation)
{
	// Play Fire Montage
	if (IsValid(Attachments[InTag]->DA_Weapon->ActionData[0].ActionMontage))
	{
		OwnerCharacter->PlayAnimMontage(Attachments[InTag]->DA_Weapon->ActionData[0].ActionMontage);
	}
	
	Multicast_Fire(InTag, HitLocation);
}

void UXZCombatHandler::Multicast_Fire_Implementation(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation)
{
	FTimerHandle FireTimerHandle;
	FTimerDelegate FireTimerDelegate = FTimerDelegate::CreateLambda([this, InTag, HitLocation]()
		{
			this->OnFire(InTag, HitLocation);
		});
	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, FireTimerDelegate, Attachments[InTag]->DA_Weapon->ActionData[0].Action_FrameTime, false);
}

void UXZCombatHandler::OnFire(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation)
{
	//FTransform SocketTransform = GetWeaponMesh()->GetSocketByName(MuzzleSocketName)->GetSocketTransform(GetWeaponMesh());
	
}

void UXZCombatHandler::OnAiming(float Output)
{
	GetFollowCamera()->FieldOfView = FMath::Lerp(Attachments[EquippedTag]->DA_Weapon->AimData.WeaponZoomData.FieldOfView, Attachments[EquippedTag]->DA_Weapon->AimData.BaseZoomData.FieldOfView, Output);
}
