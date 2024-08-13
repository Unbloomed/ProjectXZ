#include "XZWeaponComponent.h"

#include "XZStateComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Handler/XZCombatHandler.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "ProjectXZ/Character/XZCharacter.h"
#include "ProjectXZ/Character/XZPlayerController.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"
#include "ProjectXZ/Weapon/XZEquipment.h"
#include "Weapon/Attachment/XZAttachment.h"

UXZWeaponComponent::UXZWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UXZWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UXZWeaponComponent, EquippedWeaponTag, COND_None, REPNOTIFY_Always);
}

void UXZWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetXZCharacter() && GetXZCharacter()->IsLocallyControlled())
	{
		FHitResult HitResult;
		TraceUnderCrosshairs(HitResult); // Crosshair?癒?퐣 LineTrace????랁?HitResult 揶쏅?????낅쑓??꾨뱜??뺣뼄.
		HitTarget = HitResult.ImpactPoint;
	}
}

AXZCharacter* UXZWeaponComponent::GetXZCharacter()
{
	if (IsValid(OwnerCharacter)) return OwnerCharacter;

	OwnerCharacter = Cast<AXZCharacter>(GetOwner());
	return OwnerCharacter;
}

AXZPlayerController* UXZWeaponComponent::GetXZPlayerController()
{
	if (IsValid(XZPlayerController)) return XZPlayerController;

	XZPlayerController = Cast<AXZPlayerController>(GetXZCharacter()->GetController());
	return XZPlayerController;
}

void UXZWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();


	if ( false == IsValid(WeaponDataTable) ) return;

	// Create Weapon
	for ( const FGameplayTag& Tag : Init_WeaponTags )
	{
		// Use the GameplayTag's name directly as the Row ID
		FName RowName = FName(*Tag.ToString());
		//UE_LOG(LogTemp, Log, TEXT("Attempting to find row with ID: %s"), *RowName.ToString());

		FWeaponListData* FoundWeapon = WeaponDataTable->FindRow<FWeaponListData>(RowName, TEXT("Looking for weapon"), true);

		if ( FoundWeapon )
		{
			//UE_LOG(LogTemp, Log, TEXT("Found weapon with tag: %s"), *FoundWeapon->WeaponTag.ToString());
			AXZAttachment* WeaponToAdd = NewObject<AXZAttachment>(FoundWeapon->WeaponActor);
			if ( WeaponToAdd )
			{
				CombatHandler->AddNewWeapon(Tag, GetXZCharacter());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("WeaponDataAsset is null for tag: %s"), *Tag.ToString());
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No weapon found for row ID: %s"), *RowName.ToString());
		}
	}
}

void UXZWeaponComponent::AddNewWeapon(const FGameplayTag& InTag)
{
	Server_AddNewWeapon(InTag);
}

void UXZWeaponComponent::Server_AddNewWeapon_Implementation(const FGameplayTag& InTag)
{
	Multicast_AddNewWeapon(InTag);
}

void UXZWeaponComponent::Multicast_AddNewWeapon_Implementation(const FGameplayTag& InTag)
{
	FName RowName = FName(*InTag.ToString());
	FWeaponListData* FoundWeapon = WeaponDataTable->FindRow<FWeaponListData>(RowName, TEXT("Looking for weapon"), true);

	if ( FoundWeapon )
	{
		AXZAttachment* WeaponToAdd = NewObject<AXZAttachment>(FoundWeapon->WeaponActor);
		if ( WeaponToAdd )
		{
			CombatHandler->AddNewWeapon(InTag, GetXZCharacter());
		}
	}
}

void UXZWeaponComponent::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D CrosshairLocation(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f); // Center of Screen
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	); // DeprojectScreenToWorld ?源껊궗??롢늺 true, ??쎈솭??롢늺 false

	if (bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;

		if (GetXZCharacter())
		{
			float DistanceToCharacter = (GetXZCharacter()->GetActorLocation() - Start).Size();
			Start += CrosshairWorldDirection * (DistanceToCharacter + 100.0f);
			//DrawDebugSphere(GetWorld(), Start, 4.0f, 12, FColor::Blue, false); // just for Debugging purpose. To Be Deleted
		}

		FVector End = Start + CrosshairWorldDirection * 80000.0f; // TRACE_LENGTH 80000.0f

		GetWorld()->LineTraceSingleByChannel(TraceHitResult, Start, End, ECollisionChannel::ECC_Visibility);

		if (TraceHitResult.bBlockingHit == false) 
		{
			TraceHitResult.ImpactPoint = End; 
		}
	}
}

void UXZWeaponComponent::ShowCrosshair(const FGameplayTag& InTag, bool bShow)
{
	CombatHandler->ShowCrosshair(bShow);
}

void UXZWeaponComponent::EquipWeapon(const FGameplayTag& InTag)
{
	// If InTag weapon is an equipped weapon, then unequip the equipped weapon and return
	if (EquippedWeaponTag == InTag)
	{
		ShowCrosshair(InTag, false);
		UnequipWeapon(InTag);
		return;
	}

	if (EquippedWeaponTag != InTag && EquippedWeaponTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Weapon")))))
	{
		ShowCrosshair(EquippedWeaponTag, false);
		UnequipWeapon(EquippedWeaponTag); // Unequip current(=Equipped) weapon
	}

	ShowCrosshair(InTag, true);
	Server_EquipWeapon(InTag);
}

void UXZWeaponComponent::Server_EquipWeapon_Implementation(const FGameplayTag& InTag)
{
	EquippedWeaponTag = InTag;

	CombatHandler->Equip(EquippedWeaponTag);
}

void UXZWeaponComponent::OnRep_EquippedWeaponTag()
{
	CombatHandler->Equip(EquippedWeaponTag);
}

void UXZWeaponComponent::UnequipWeapon(const FGameplayTag& InTag)
{
	Server_UnequipWeapon(InTag);
}

void UXZWeaponComponent::Server_UnequipWeapon_Implementation(const FGameplayTag& InTag)
{
	if (EquippedWeaponTag == InTag)
	{
		EquippedWeaponTag = FXZTags::GetXZTags().Fist;
	}
	else
	{
		EquippedWeaponTag = InTag;
	}

	CombatHandler->Unequip(EquippedWeaponTag);
}

void UXZWeaponComponent::Multicast_UnequipWeapon_Implementation(const FGameplayTag& InTag)
{
	
}

void UXZWeaponComponent::Fire()
{
	CombatHandler->Fire(EquippedWeaponTag, HitTarget);
}

void UXZWeaponComponent::Reload(const FGameplayTag& InTag)
{

}

void UXZWeaponComponent::Server_Reload_Implementation(const FGameplayTag& InTag, const FTransform& SocketTransform)
{
	
}

void UXZWeaponComponent::Multicast_Reload_Implementation(const FGameplayTag& InTag, const FTransform& SocketTransform)
{
	
}

void UXZWeaponComponent::Aiming(bool bAiming)
{
	if (false == IsValid(GetXZCharacter())) return;
	if (false == EquippedWeaponTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Weapon"))))) return;
	
	if (bAiming)
	{
		CombatHandler->StartAiming();
	}
	else
	{
		CombatHandler->EndAiming();
	}

	Server_Aiming(bAiming);
}

void UXZWeaponComponent::Server_Aiming_Implementation(bool bAiming)
{
	if (bAiming)
	{
		GetXZCharacter()->GetStateComponent()->SetState(FXZTags::GetXZTags().StateTag_Alive_Equip_Aim);
		GetXZCharacter()->GetCharacterMovement()->MaxWalkSpeed = AimWalkSpeed;
	}
	else
	{
		GetXZCharacter()->GetStateComponent()->SetState(FXZTags::GetXZTags().StateTag_Alive_Equip_Idle);
		GetXZCharacter()->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}


void UXZWeaponComponent::Init()
{
	CombatHandler = CreateCombatHandler();
}

UXZCombatHandler* UXZWeaponComponent::CreateCombatHandler()
{
	return NewObject<UXZCombatHandler>(this, UXZCombatHandler::StaticClass());;
}

UXZCombatHandler* UXZWeaponComponent::GetCombatHandler()
{
	if (IsValid(CombatHandler))
	{
		return CombatHandler;
	}

	CombatHandler = CreateCombatHandler();
	return CombatHandler;
}
