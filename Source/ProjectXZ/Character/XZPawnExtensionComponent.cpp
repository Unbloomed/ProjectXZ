#include "XZPawnExtensionComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "XZCharacter.h"
#include "Component/XZInventoryComponent.h"
#include "ProjectXZ/Component/XZInputComponent.h"
#include "ProjectXZ/Component/XZWeaponComponent.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"

UXZPawnExtensionComponent::UXZPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	//PawnData = nullptr;
}

TObjectPtr<AXZCharacter> UXZPawnExtensionComponent::GetXZCharacter()
{
	if (IsValid(XZCharacter)) return XZCharacter;

	XZCharacter = GetPawn<AXZCharacter>();
	return XZCharacter;
}

void UXZPawnExtensionComponent::CheckDefaultInitialization()
{
	// Before checking our progress, try progressing any other features we might depend on
	CheckDefaultInitializationForImplementers();

	//static const TArray<FGameplayTag> StateChain = { LyraGameplayTags::InitState_Spawned, LyraGameplayTags::InitState_DataAvailable, LyraGameplayTags::InitState_DataInitialized, LyraGameplayTags::InitState_GameplayReady };

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	//ContinueInitStateChain(StateChain);
}

void UXZPawnExtensionComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}

	UXZInputComponent* XZInputComponent = Cast<UXZInputComponent>(PlayerInputComponent);
	if (false == IsValid(XZInputComponent)) UE_LOG(LogTemp, Warning, TEXT("nullptr == XZInputComponent"));

	if (IsValid(XZInputComponent))
	{
		// Pressed Only
		XZInputComponent->BindPressActions(InputConfig, FXZTags::GetXZTags().InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		XZInputComponent->BindPressActions(InputConfig, FXZTags::GetXZTags().InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse);
		XZInputComponent->BindPressActions(InputConfig, FXZTags::GetXZTags().InputTag_Crouch, ETriggerEvent::Triggered, this, &ThisClass::Input_Crouch);

		XZInputComponent->BindPressActions(InputConfig, FXZTags::GetXZTags().InputTag_PickupItem, ETriggerEvent::Triggered, this, &ThisClass::Input_PickupItem);
		
		XZInputComponent->BindPressActions(InputConfig, FXZTags::GetXZTags().InputTag_1, ETriggerEvent::Triggered, this, &ThisClass::Input_EquipSlot1);
		XZInputComponent->BindPressActions(InputConfig, FXZTags::GetXZTags().InputTag_2, ETriggerEvent::Triggered, this, &ThisClass::Input_EquipSlot2);
		XZInputComponent->BindPressActions(InputConfig, FXZTags::GetXZTags().InputTag_Weapon_Fire, ETriggerEvent::Triggered, this, &ThisClass::Input_WeaponFire);
		XZInputComponent->BindPressActions(InputConfig, FXZTags::GetXZTags().InputTag_Weapon_Reload, ETriggerEvent::Triggered, this, &ThisClass::Input_WeaponReload);

		// Pressed & Released
		XZInputComponent->BindPressReleaseActions(InputConfig, this, &ThisClass::Input_Jump, &ThisClass::Input_StopJumping);
		XZInputComponent->BindPressReleaseActions(InputConfig, this, &ThisClass::Input_Aim, &ThisClass::Input_StopAiming);
	}
}

void UXZPawnExtensionComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	if (IsValid(Controller))
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UXZPawnExtensionComponent::Input_Jump(FGameplayTag InputTag)
{
	if (false == InputTag.MatchesTagExact(FXZTags::GetXZTags().InputTag_Jump)) return;

	if (ACharacter* Character = GetPawn<ACharacter>())
	{
		Character->Jump();
	}
}

void UXZPawnExtensionComponent::Input_StopJumping(FGameplayTag InputTag)
{
	if (false == InputTag.MatchesTagExact(FXZTags::GetXZTags().InputTag_StopJumping)) return;

	if (ACharacter* Character = GetPawn<ACharacter>())
	{
		Character->StopJumping();
	}
}


void UXZPawnExtensionComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	if (false == IsValid(Pawn)) return;

	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

void UXZPawnExtensionComponent::Input_Crouch(const FInputActionValue& InputActionValue)
{
	if (AXZCharacter* Character = GetPawn<AXZCharacter>())
	{
		if (Character->CanCrouch())
		{
			UE_LOG(LogTemp, Log, TEXT("Crouch"));
			Character->Crouch();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Uncrouch"));
			Character->UnCrouch();
		}
	}
}

void UXZPawnExtensionComponent::Input_PickupItem(const FInputActionValue& InputActionValue)
{
	if (GetXZCharacter() && GetXZCharacter()->GetInventoryComponent())
	{
		GetXZCharacter()->GetInventoryComponent()->PickupItem();
	}
}

void UXZPawnExtensionComponent::Input_EquipSlot1(const FInputActionValue& InputActionValue)
{
	if (GetXZCharacter() && GetXZCharacter()->GetWeaponComponent())
	{
		GetXZCharacter()->GetWeaponComponent()->EquipWeapon(
			GetXZCharacter()->GetInventoryComponent()->GetEquipSlot1());
	}
}

void UXZPawnExtensionComponent::Input_EquipSlot2(const FInputActionValue& InputActionValue)
{
	if (GetXZCharacter() && GetXZCharacter()->GetWeaponComponent())
	{
		GetXZCharacter()->GetWeaponComponent()->EquipWeapon(
			GetXZCharacter()->GetInventoryComponent()->GetEquipSlot2());
	}
}

void UXZPawnExtensionComponent::Input_EquipSlot3(const FInputActionValue& InputActionValue)
{
	if (GetXZCharacter() && GetXZCharacter()->GetWeaponComponent())
	{
		GetXZCharacter()->GetWeaponComponent()->EquipWeapon(
			GetXZCharacter()->GetInventoryComponent()->GetEquipSlot3());
	}
}

void UXZPawnExtensionComponent::Input_EquipSlot4(const FInputActionValue& InputActionValue)
{
	if (GetXZCharacter() && GetXZCharacter()->GetWeaponComponent())
	{
		GetXZCharacter()->GetWeaponComponent()->EquipWeapon(
			GetXZCharacter()->GetInventoryComponent()->GetEquipSlot4());
	}
}

void UXZPawnExtensionComponent::Input_WeaponReload(const FInputActionValue& InputActionValue)
{
	if (GetXZCharacter() && GetXZCharacter()->GetWeaponComponent())
	{
		UE_LOG(LogTemp, Log, TEXT("Reload"));
		// TODO : 현재 Tag 하드코딩한거 로직짜기
		FGameplayTag Tag = FXZTags::GetXZTags().Weapon_Projectile_Rifle;
		GetXZCharacter()->GetWeaponComponent()->Reload(Tag);
	}
}

void UXZPawnExtensionComponent::Input_Aim(FGameplayTag InputTag)
{
	if (false == InputTag.MatchesTagExact(FXZTags::GetXZTags().InputTag_Weapon_Aim)) return;

	if (GetXZCharacter() && GetXZCharacter()->GetWeaponComponent())
	{
		GetXZCharacter()->GetWeaponComponent()->StartAiming();
	}
}

void UXZPawnExtensionComponent::Input_StopAiming(FGameplayTag InputTag)
{
	if (false == InputTag.MatchesTagExact(FXZTags::GetXZTags().InputTag_Weapon_StopAiming)) return;

	if (GetXZCharacter() && GetXZCharacter()->GetWeaponComponent())
	{
		GetXZCharacter()->GetWeaponComponent()->EndAiming();
	}
}

void UXZPawnExtensionComponent::Input_WeaponFire(const FInputActionValue& InputActionValue)
{
	if (GetXZCharacter() && GetXZCharacter()->GetWeaponComponent())
	{
		GetXZCharacter()->GetWeaponComponent()->Fire();
	}
}
