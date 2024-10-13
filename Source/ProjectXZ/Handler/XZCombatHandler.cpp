#include "Handler/XZCombatHandler.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Character/XZCharacter.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Manager/XZDataManager.h"
#include "Weapon/XZDA_Weapon.h"
#include "Weapon/Attachment/XZAttachment.h"

void UXZCombatHandler::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UXZCombatHandler, bEquipped, COND_None, REPNOTIFY_Always);
}

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
	//if (IsValidWeapon(InTag)) { return; }

	OwnerCharacter = InOwner;
	
	WeaponDataTable = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance())->GetWeaponDataTable();
	checkf(WeaponDataTable, TEXT("No Weapon DataTable. Check UXZWeaponComponent::AddNewWeapon"));

	FWeaponListData* FoundWeapon = GetDataTableRowByTag<FWeaponListData>(WeaponDataTable, InTag);
	if ( FoundWeapon && FoundWeapon->WeaponActor )
	{
		FActorSpawnParameters Params;
		Params.Owner = OwnerCharacter;
		AXZAttachment* WeaponToAdd = OwnerCharacter->GetWorld()->SpawnActor<AXZAttachment>(FoundWeapon->WeaponActor, Params);
		
		// Add New Weapon to TMap list
		Attachments.Add({ InTag, WeaponToAdd });
		ChangeSocket_Unequip(InTag);
	}

	for (const auto& iter : Attachments)
	{
		UE_LOG(LogTemp, Log, TEXT("%s, %s"), *(OwnerCharacter->GetName()), *(iter.Value->GetName()));
	}
}

void UXZCombatHandler::Server_AddNewWeapon_Implementation(const FGameplayTag& InTag)
{
	
}

void UXZCombatHandler::Client_AddNewWeapon_Implementation(const FGameplayTag& InTag)
{
	
}

void UXZCombatHandler::Equip(const FGameplayTag& InTag)
{
	if ( false == IsValid(OwnerCharacter) ) { return; }
	
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

		if (Attachments[InTag]->DA_Weapon)
		{
			UE_LOG(LogTemp, Log, TEXT("%s %f"), *(Attachments[InTag]->DA_Weapon->GetName()), Attachments[InTag]->DA_Weapon->EquipmentData.Equip_FrameTime);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No DA_Weapon Data"));
		}
		
		EquippedTag = InTag;
		bEquipped = true;
	}

	
	/*
	 
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
	
	*/
}

void UXZCombatHandler::Unequip(const FGameplayTag& InTag)
{
	if ( false == IsValid(OwnerCharacter) ) { return; }
	
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
	if ( Attachments[InTag]->DA_Weapon->EquipmentData.HolsterSocketName.IsValid() )
	{
		Attachments[InTag]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Attachments[InTag]->DA_Weapon->EquipmentData.HolsterSocketName);
	}
}

void UXZCombatHandler::OnRep_bEquipped()
{
	UE_LOG(LogTemp, Log, TEXT("bEquipped = %c"), bEquipped);
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
	if (false == InTag.IsValid()) { return; }
	
	// Play Fire Montage
	if (IsValid(Attachments[InTag]->DA_Weapon->ActionData[0].ActionMontage))
	{
		OwnerCharacter->PlayAnimMontage(Attachments[InTag]->DA_Weapon->ActionData[0].ActionMontage);
	}
	
	// Fire - Spawn Projectile 
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
